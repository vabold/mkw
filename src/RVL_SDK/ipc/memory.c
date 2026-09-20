/// \file RVL_SDK/ipc/memory.c
///
/// Sources:
///     [RJTJ01] Minna no Joushiki Ryoku TV
///     [RDCE78] Deadly Creatures
///     [SC5PGN] Challenge Me: Word Puzzles
///     [IOSU] Wii U OSv10-v15848/code/fw.img
///
/// SPDX-License-Identifier: CC0-1.0

#include <RVL_SDK/os.h>
#include <RVL_SDK/private/ipc.h>
#include <RVL_SDK/private/memory.h>

/// Magic values for IOSHeapChunk
typedef enum
{
    IOS_HEAP_CHUNK_MAGIC_FREE = 0xbabe0000,  /// A free chunk
    IOS_HEAP_CHUNK_MAGIC_USED = 0xbabe0001,  /// A used chunk
    IOS_HEAP_CHUNK_MAGIC_ALIGN = 0xbabe0002, /// A sub-chunk used for alignment
} IOS_HEAP_CHUNK_MAGIC;

/// Memory chunk for IOS heap
typedef struct IOSHeapChunk IOSHeapChunk;
struct IOSHeapChunk
{
    IOS_HEAP_CHUNK_MAGIC magic; /// Chunk magic value
    u32 size;                   /// Chunk size
    IOSHeapChunk *prev;         /// Previous free chunk (or parent in case of ALIGN)
    IOSHeapChunk *next;         /// Next free chunk
};

// [IOSU] "Heap with base %p, size 0x%x, owned by pid %d, has encountered invalid chunk %p."
/// Handle for an IOS heap
typedef struct
{
    u8 *base;                /// Base of full heap memory block
    u32 owner;               /// Owner PID (process ID); only used in IOS
    u32 size;                /// Size of full heap memory block
    IOSHeapChunk *freeChunk; /// The first available free chunk
} IOSHeapHandle;

static IOSHeapHandle __heaps[ IOS_HEAP_MAX ]; /// Managed handles for each IOS heap

/// Merge two free chunks together to form one, larger free chunk
static void __iosCoalesceChunk( IOSHeapChunk *chunk )
{
    if( chunk != NULL && (u8 *)chunk->next == (u8 *)chunk + chunk->size + sizeof( IOSHeapChunk ) )
    {
        IOSHeapChunk *next = chunk->next;
        chunk->next = next->next;
        if( chunk->next )
        {
            chunk->next->prev = chunk;
        }
        chunk->size += next->size + sizeof( IOSHeapChunk );
    }
}

IOSHeapId iosCreateHeap( void *base, u32 size )
{
    IOSHeapId rv = IOS_ERROR_INVALID;
    BOOL enabled = OSDisableInterrupts( );

    if( ( (u32)base & 31 ) == 0 )
    {
        IOSHeapId hid;
        for( hid = 0; hid < IOS_HEAP_MAX; hid++ )
        {
            if( __heaps[ hid ].base == NULL )
            {
                break;
            }
        }
        if( hid == IOS_HEAP_MAX )
        {
            rv = IOS_ERROR_MAX;
        }
        else
        {
            IOSHeapHandle *heap = &__heaps[ hid ];

            heap->base = (u8 *)base;
            heap->size = size;
            heap->freeChunk = (IOSHeapChunk *)base;

            heap->freeChunk->magic = 0xbabe0000;
            heap->freeChunk->size = size - sizeof( IOSHeapChunk );
            heap->freeChunk->prev = NULL;
            heap->freeChunk->next = NULL;

            rv = hid;
        }
    }

    OSRestoreInterrupts( enabled );
    return rv;
}

IOSError iosDestroyHeap( IOSHeapId hid )
{
    IOSError rv = IOS_ERROR_INVALID;
    BOOL enabled = OSDisableInterrupts( );

    if( hid < 0 || hid >= IOS_HEAP_MAX || __heaps[ hid ].base == NULL )
    {
        rv = IOS_ERROR_INVALID;
    }
    else if( hid == 0 )
    {
        rv = IOS_ERROR_ACCESS;
    }
    else
    {
        IOSHeapHandle *heap = &__heaps[ hid ];

        heap->base = NULL;
        heap->size = 0;
        heap->owner = 0;
        heap->freeChunk = NULL;

        rv = IOS_ERROR_OK;
    }

    OSRestoreInterrupts( enabled );
    return rv;
}

void *__iosAlloc( IOSHeapId hid, s32 size, u32 align )
{
    void *ptr = NULL;
    BOOL enabled = OSDisableInterrupts( );
    s32 alignOffset;
    IOSHeapHandle *heap;
    IOSHeapChunk *chunk, *match;

    if( size == 0 || align == 0 || ( align & align - 1 ) )
    {
        goto out;
    }

    if( align < 0x20 )
    {
        align = 0x20;
    }
    size = size + 0x1f & ~0x1f;

    if( hid < 0 || hid >= IOS_HEAP_MAX || __heaps[ hid ].base == NULL )
    {
        ptr = NULL;
        goto out;
    }

    heap = &__heaps[ hid ];
    chunk = heap->freeChunk;
    match = NULL;
    // Find the smallest size chunk the size would fit into
    while( chunk != NULL )
    {
        alignOffset = ( align - 1 ) & ( align - ( (u32)( chunk + 1 ) & align - 1 ) );

        if( chunk->size == size && alignOffset == 0 )
        {
            // Perfect match; break early
            match = chunk;
            break;
        }

        if( chunk->size >= size + alignOffset && ( match == NULL || chunk->size < match->size ) )
        {
            // The best match so far
            match = chunk;
        }

        chunk = chunk->next;
    }

    if( match == NULL )
    {
        goto out;
    }

    alignOffset = ( align - 1 ) & ( align - ( (u32)( match + 1 ) & align - 1 ) );
    if( match->size > size + alignOffset + sizeof( IOSHeapChunk ) )
    {
        // Split the extra space at the end into its own chunk
        IOSHeapChunk *splitChunk =
                (IOSHeapChunk *)( (u8 *)match + size + alignOffset + sizeof( IOSHeapChunk ) );

        splitChunk->magic = IOS_HEAP_CHUNK_MAGIC_FREE;
        splitChunk->size = match->size - size - alignOffset - sizeof( IOSHeapChunk );
        splitChunk->next = match->next;
        if( splitChunk->next != NULL )
        {
            splitChunk->next->prev = splitChunk;
        }
        match->next = splitChunk;
        match->size = size + alignOffset;
    }

    match->magic = IOS_HEAP_CHUNK_MAGIC_USED;

    // These links are only for free chunks
    if( match->prev != NULL )
    {
        match->prev->next = match->next;
    }
    else
    {
        heap->freeChunk = match->next;
    }
    if( match->next != NULL )
    {
        match->next->prev = match->prev;
    }
    match->prev = match->next = NULL;

    ptr = (u8 *)match + alignOffset + sizeof( IOSHeapChunk );
    if( alignOffset != 0 )
    {
        IOSHeapChunk *alignChunk = (IOSHeapChunk *)( (u8 *)ptr - sizeof( IOSHeapChunk ) );
        alignChunk->magic = IOS_HEAP_CHUNK_MAGIC_ALIGN;
        alignChunk->prev = match;
    }

out:
    OSRestoreInterrupts( enabled );
    return ptr;
}

void *iosAllocAligned( IOSHeapId hid, s32 size, u32 align )
{
    return __iosAlloc( hid, size, align );
}

IOSError iosFree( IOSHeapId hid, void *ptr )
{
    IOSError rv = IOS_ERROR_INVALID;
    BOOL enabled = OSDisableInterrupts( );
    IOSHeapHandle *heap;
    IOSHeapChunk *chunk, *freeChunk;

    if( ptr == NULL )
    {
        goto out;
    }

    if( hid < 0 || hid >= IOS_HEAP_MAX || __heaps[ hid ].base == NULL )
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    // Check that the pointer is actually within the heap
    heap = &__heaps[ hid ];
    if( (u8 *)ptr < heap->base + sizeof( IOSHeapChunk ) || (u8 *)ptr > heap->base + heap->size )
    {
        goto out;
    }

    chunk = (IOSHeapChunk *)( (u8 *)ptr - sizeof( IOSHeapChunk ) );
    if( chunk->magic == IOS_HEAP_CHUNK_MAGIC_ALIGN )
    {
        // Get parent of alignment block
        chunk = chunk->prev;
    }

    if( chunk->magic != IOS_HEAP_CHUNK_MAGIC_USED )
    {
        // This is not a chunk or it's already free!!
        goto out;
    }

    chunk->magic = IOS_HEAP_CHUNK_MAGIC_FREE; // Set to free

    // Find the next free chunk
    for( freeChunk = heap->freeChunk; freeChunk != NULL; freeChunk = freeChunk->next )
    {
        if( freeChunk->next == NULL || freeChunk->next > chunk )
        {
            break;
        }
    }

    if( freeChunk != NULL && chunk > freeChunk )
    {
        chunk->prev = freeChunk;
        chunk->next = freeChunk->next;
        freeChunk->next = chunk;
        if( chunk->next != NULL )
        {
            chunk->next->prev = chunk;
        }
    }
    else
    {
        chunk->next = heap->freeChunk;
        heap->freeChunk = chunk;
        chunk->prev = NULL;
        if( chunk->next != NULL )
        {
            chunk->next->prev = chunk;
        }
    }

    __iosCoalesceChunk( chunk );
    __iosCoalesceChunk( chunk->prev );
    rv = IOS_ERROR_OK;

out:
    OSRestoreInterrupts( enabled );
    return rv;
}
