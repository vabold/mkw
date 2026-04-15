#include <RVL_SDK/arc.h>
// #include <ctype.h> // needs MSL
#include <RVL_SDK/os.h>

#undef ADD_PTR
#define ADD_PTR( ptr, offset ) ( (void *)( (u32)ptr + offset ) )

#undef IS_DIR
#define IS_DIR( fst, entrynum ) \
    ( ( fst[ entrynum ].isDirAndStringOff & 0xff000000 ) == 0 ? FALSE : TRUE )

#define ARC_FILE_MAGIC 0x55aa382d

typedef struct
{
    unsigned int magic;
    int fstStart;
    int fstSize;
    int fileStart;
    int reserve[ 4 ];
} ARCHeader;

typedef struct FSTEntry
{
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
} FSTEntry;

BOOL ARCInitHandle( void *arcStart, ARCHandle *handle )
{
    FSTEntry *FSTEntries;
    ARCHeader *arcHeader = (ARCHeader *)arcStart;

    if( arcHeader->magic != ARC_FILE_MAGIC )
    {
#line 74
        OSError( "ARCInitHandle: bad archive format" );
    }

    handle->archiveStartAddr = arcStart;

    FSTEntries = (FSTEntry *)ADD_PTR( arcStart, arcHeader->fstStart );
    handle->FSTStart = FSTEntries;
    handle->fileStart = ADD_PTR( arcStart, arcHeader->fileStart );

    OSAssertMessage( FSTEntries != NULL, "ARCInitHandle: bad archive format" );

    handle->entryNum = FSTEntries[ 0 ].nextEntryOrLength;
    handle->FSTStringStart = (char *)ADD_PTR( FSTEntries, handle->entryNum * sizeof( FSTEntry ) );
    handle->FSTLength = arcHeader->fstSize;
    handle->currDir = 0;

    return TRUE;
}

BOOL ARCOpen( ARCHandle *handle, const char *fileName, ARCFileInfo *af )
{
    s32 entry;
    char currentDir[ 128 ];
    FSTEntry *FSTEntries;

    OSAssertMessage( handle, "ARCOpen(): NULL pointer is specified to ARCHandle structure" );
    OSAssertMessage( fileName, "ARCOpen(): NULL pointer is specified to fileName" );
    OSAssertMessage( af, "ARCOpen(): NULL pointer is specified to ARCFileInfo structure" );

    FSTEntries = (FSTEntry *)handle->FSTStart;
    entry = ARCConvertPathToEntrynum( handle, fileName );

    if( entry < 0 )
    {
        ARCGetCurrentDir( handle, currentDir, sizeof( currentDir ) );
        OSReport( "Warning: ARCOpen(): file '%s' was not found under %s in the archive.\n",
                fileName, currentDir );
        return FALSE;
    }

    OSAssertMessage( !IS_DIR( FSTEntries, entry ), "ARCOpen(): %s is a directory", fileName );

    if( entry < 0 || IS_DIR( FSTEntries, entry ) )
    {
        return FALSE;
    }

    af->handle = handle;
    af->startOffset = FSTEntries[ entry ].parentOrPosition;
    af->length = FSTEntries[ entry ].nextEntryOrLength;

    return TRUE;
}

BOOL ARCFastOpen( ARCHandle *handle, s32 entrynum, ARCFileInfo *af )
{
    FSTEntry *FSTEntries;

    OSAssertMessage( handle, "ARCFastOpen(): null pointer is specified to ARCHandle address  " );
    OSAssertMessage( af, "ARCFastOpen(): null pointer is specified to ARCFileInfo address  " );
    OSAssertMessage( entrynum >= 0 && entrynum < handle->entryNum,
            "ARCFastOpen(): specified entry number '%d' is out of range  ", entrynum );

    FSTEntries = (FSTEntry *)handle->FSTStart;

    OSAssertMessage( !IS_DIR( FSTEntries, entrynum ),
            "ARCFastOpen(): entry number '%d' is assigned to a directory  ", entrynum );

    if( !( entrynum >= 0 && entrynum < handle->entryNum ) || IS_DIR( FSTEntries, entrynum ) )
    {
        return FALSE;
    }

    af->handle = handle;
    af->startOffset = FSTEntries[ entrynum ].parentOrPosition;
    af->length = FSTEntries[ entrynum ].nextEntryOrLength;

    return TRUE;
}

// Subroutine for ARCConvertPathToEntrynum
static BOOL isSame( const char *path, const char *string )
{
    while( *string != '\0' )
    {
        if( tolower( *path++ ) != tolower( *string++ ) )
        {
            return FALSE;
        }
    }

    // '/' if we found the directory, '\0' if we found the file (or directory with no suffix)
    // The caller will delineate between file and directory by checking the FST entry
    if( *path == '/' || *path == '\0' )
    {
        return TRUE;
    }

    return FALSE;
}

s32 ARCConvertPathToEntrynum( ARCHandle *handle, const char *pathPtr )
{
    const char *ptr;
    const char *stringPtr;
    BOOL isDir;
    s32 length;
    u32 dirLookAt;
    u32 i;
    const char *origPathPtr = pathPtr; // Unused
    FSTEntry *FSTEntries;

    OSAssertMessage( handle,
            "ARCConvertPathToEntrynum(): null pointer is specified to ARCHandle structure" );
    OSAssertMessage( pathPtr,
            "ARCConvertPathToEntrynum(): null pointer is specified to file name" );

    dirLookAt = handle->currDir;
    FSTEntries = (FSTEntry *)handle->FSTStart;

    while( TRUE )
    {
        if( pathPtr[ 0 ] == '\0' )
        {
            // We found the directory (always a directory)
            return dirLookAt;
        }
        else if( pathPtr[ 0 ] == '/' )
        {
            // Restart at root
            dirLookAt = 0;
            ++pathPtr;
            continue;
        }
        else if( pathPtr[ 0 ] == '.' )
        {
            if( pathPtr[ 1 ] == '.' )
            {
                if( pathPtr[ 2 ] == '/' )
                {
                    // Restart at parent directory
                    dirLookAt = FSTEntries[ dirLookAt ].parentOrPosition;
                    pathPtr += 3;
                    continue;
                }
                else if( pathPtr[ 2 ] == '\0' )
                {
                    // We found the parent directory (always a directory)
                    return FSTEntries[ dirLookAt ].parentOrPosition;
                }
            }
            else if( pathPtr[ 1 ] == '/' )
            {
                // Restart at current directory
                pathPtr += 2;
                continue;
            }
            else if( pathPtr[ 1 ] == '\0' )
            {
                // We found the current directory (always a directory)
                return dirLookAt;
            }
        }

        // Prep a substring formed by [pathPtr, ptr)
        // We need this to compute the length so we can keep iterating later
        for( ptr = pathPtr; *ptr != '\0' && *ptr != '/'; ++ptr )
        {
        }

        // We need to iterate over all the items in the directory and see if the substring matches
        // Example: first we search [a]/b/c, then a/[b]/c, and finally find the leaf a/b/[c]
        // If ptr is '/', we need to find the search the next layer down and restart
        // If ptr is '\0', we need to find the file/subdirectory in that directory

        // NOTE: isDir == TRUE guarantees it's a directory but it can still be a directory if FALSE
        isDir = *ptr == '\0' ? FALSE : TRUE;
        length = ptr - pathPtr;
        ptr = pathPtr; // Why?? There's no writes to pathPtr in the loop

        for( i = dirLookAt + 1; i < FSTEntries[ dirLookAt ].nextEntryOrLength;
                i = IS_DIR( FSTEntries, i ) ? FSTEntries[ i ].nextEntryOrLength : i + 1 )
        {
            // We need a nested loop with no condition so that we can handle an edgecase
            // If the directory includes itself, we need to move onto the next FST entry
            // We can't do that in one loop without triggering the incrementer, so use a nested loop
            while( TRUE )
            {
                if( !IS_DIR( FSTEntries, i ) && isDir == TRUE )
                {
                    break;
                }

                stringPtr =
                        handle->FSTStringStart + ( FSTEntries[ i ].isDirAndStringOff & 0xffffff );
                // The directory includes itself, skip it
                if( stringPtr[ 0 ] == '.' && stringPtr[ 1 ] == '\0' )
                {
                    ++i;
                    continue;
                }

                if( isSame( ptr, stringPtr ) == TRUE )
                {
                    // NOTE: This goto is to delineate natural vs unnatural loop exiting
                    // This emulates Python's loop/else pattern
                    goto found;
                }

                break;
            }
        }

        // Natural fallthrough: We searched through the whole directory and didn't find it
        // Therefore, this path does not exist under these search conditions
        return -1;

    found:
        // Unnatural fallthrough: If it's a leaf, we found it
        if( isDir == FALSE )
        {
            return i;
        }

        // Otherwise, we restart in the subdirectory we found
        dirLookAt = i;
        pathPtr += length + 1;
    }

    return -1;
}

BOOL ARCEntrynumIsDir( const ARCHandle *handle, s32 entrynum )
{
    FSTEntry *FSTEntries;

    OSAssertMessage( handle,
            "ARCEntrynumIsDir(): null pointer is specified to ARCHandle structure" );
    OSAssertMessage( entrynum >= 0,
            "ARCEntrynumIsDir(): no file/directory is specified to entrynum" );

    FSTEntries = (FSTEntry *)handle->FSTStart;
    return IS_DIR( FSTEntries, entrynum );
}

// Subroutine for ARCConvertEntrynumToPath
static u32 myStrncpy( char *dest, char *src, u32 maxlen )
{
    u32 i = maxlen;
    for( ; i != 0 && *src != '\0'; --i )
    {
        *dest++ = *src++;
    }
    return maxlen - i;
}

// Subroutine for ARCConvertEntrynumToPath
static u32 entryToPath( ARCHandle *handle, u32 entry, char *path, u32 maxlen )
{
    char *name;
    u32 loc;
    FSTEntry *FSTEntries = (FSTEntry *)handle->FSTStart;

    if( entry == 0 )
    {
        return 0;
    }

    name = handle->FSTStringStart + ( FSTEntries[ entry ].isDirAndStringOff & 0xffffff );
    loc = entryToPath( handle, FSTEntries[ entry ].parentOrPosition, path, maxlen );
    if( loc == maxlen )
    {
        return loc;
    }

    path[ loc++ ] = '/';
    loc += myStrncpy( path + loc, name, maxlen - loc );
    return loc;
}

static BOOL ARCConvertEntrynumToPath( ARCHandle *handle, s32 entrynum, char *path, u32 maxlen )
{
    u32 loc;
    FSTEntry *FSTEntries = (FSTEntry *)handle->FSTStart;

    OSAssertMessage( entrynum >= 0 && entrynum < handle->entryNum,
            "ARCConvertEntrynumToPath: specified entrynum(%d) is out of range  ", entrynum );
    OSAssertMessage( maxlen > 1,
            "ARCConvertEntrynumToPath: maxlen should be more than 1 (%d is specified)", maxlen );
    OSAssertMessage( IS_DIR( FSTEntries, entrynum ),
            "ARCConvertEntrynumToPath: cannot convert an entry num for a file to path  " );

    loc = entryToPath( handle, entrynum, path, maxlen );
    if( loc == maxlen )
    {
        path[ maxlen - 1 ] = '\0';
        return FALSE;
    }

    // This is always asserted to be the case, what are we doing?
    if( IS_DIR( FSTEntries, entrynum ) )
    {
        if( loc == maxlen - 1 )
        {
            path[ loc ] = '\0';
            return FALSE;
        }

        path[ loc++ ] = '/';
    }

    path[ loc ] = '\0';
    return TRUE;
}

BOOL ARCGetCurrentDir( ARCHandle *handle, char *path, u32 maxlen )
{
    OSAssertMessage( maxlen > 1, "ARCGetCurrentDir: maxlen should be more than 1 (%d is specified)",
            maxlen );
    return ARCConvertEntrynumToPath( handle, handle->currDir, path, maxlen );
}

void *ARCGetStartAddrInMem( ARCFileInfo *af )
{
    ARCHandle *handle = af->handle;

    // Out of order?
    OSAssertMessage( handle,
            "ARCGetFileAddr(): af->handle is null pointer. Maybe it's not initialized properly" );
    OSAssertMessage( af, "ARCGetFileAddr(): null pointer is specified to ARCFileInfo structure" );
    return ADD_PTR( handle->archiveStartAddr, af->startOffset );
}

u32 ARCGetStartOffset( ARCFileInfo *af )
{
    return af->startOffset;
}

u32 ARCGetLength( ARCFileInfo *af )
{
    return af->length;
}

BOOL ARCClose( ARCFileInfo *af )
{
#pragma unused( af )
    return TRUE;
}

BOOL ARCChangeDir( ARCHandle *handle, const char *dirName )
{
    s32 entry;
#ifdef DEBUG // infer ifdef based on DWARF line spacing
    char currentDir[ 128 ];
#endif
    FSTEntry *FSTEntries;

    OSAssertMessage( handle, "ARCChangeDir(): null pointer is specified to ARCHandle" );
    OSAssertMessage( dirName, "ARCChangeDir(): null pointer is specified to dirname" );

    entry = ARCConvertPathToEntrynum( handle, dirName );
    FSTEntries = (FSTEntry *)handle->FSTStart;
#ifdef DEBUG
    if( entry < 0 )
    {
        ARCGetCurrentDir( handle, currentDir, sizeof( currentDir ) );
        OSError( "ARCOpendir(): directory '%s' is not found under %s  ", dirName, currentDir );
    }
#endif
    OSAssertMessage( IS_DIR( FSTEntries, entry ), "ARCChangeDir(): %s is not a directory",
            dirName );

    if( entry < 0 || !IS_DIR( FSTEntries, entry ) )
    {
        return FALSE;
    }

    handle->currDir = entry;
    return TRUE;
}

BOOL ARCOpenDir( ARCHandle *handle, const char *dirName, ARCDir *dir )
{
    s32 entry;
    FSTEntry *FSTEntries;
#ifdef DEBUG // infer ifdef based on DWARF line spacing
    char currentDir[ 128 ];
#endif

    OSAssertMessage( handle, "ARCOpenDir(): null pointer is specified to ARCHandle" );
    OSAssertMessage( dirName, "ARCOpenDir(): null pointer is specified to ARCDir" );

    entry = ARCConvertPathToEntrynum( handle, dirName );
    FSTEntries = (FSTEntry *)handle->FSTStart;
#ifdef DEBUG
    if( entry < 0 )
    {
        ARCGetCurrentDir( handle, currentDir, sizeof( currentDir ) );
        OSError( "ARCOpendir(): directory '%s' is not found under %s  ", dirName, currentDir );
    }
#endif
    OSAssertMessage( IS_DIR( FSTEntries, entry ), "ARCOpenDir(): %s is a regular file", dirName );

    if( entry < 0 || !IS_DIR( FSTEntries, entry ) )
    {
        return FALSE;
    }

    dir->handle = handle;
    dir->entryNum = entry;
    dir->location = entry + 1;
    dir->next = FSTEntries[ entry ].nextEntryOrLength;
    return TRUE;
}

BOOL ARCReadDir( ARCDir *dir, ARCDirEntry *dirent )
{
    u32 loc;
    FSTEntry *FSTEntries;
    ARCHandle *handle = dir->handle;

    OSAssertMessage( handle,
            "ARCReadDir: dir->handle is null pointer. Maybe it's not initialized properly" );

    FSTEntries = (FSTEntry *)handle->FSTStart;
    loc = dir->location;

    while( TRUE )
    {
        if( loc <= dir->entryNum || dir->next <= loc )
        {
            return FALSE;
        }

        dirent->handle = handle;
        dirent->entryNum = loc;
        dirent->isDir = IS_DIR( FSTEntries, loc );
        dirent->name = handle->FSTStringStart + ( FSTEntries[ loc ].isDirAndStringOff & 0xffffff );
        if( dirent->name[ 0 ] == '.' && dirent->name[ 1 ] == '\0' )
        {
            ++loc;
            continue;
        }

        break;
    }

    dir->location = IS_DIR( FSTEntries, loc ) ? FSTEntries[ loc ].nextEntryOrLength : loc + 1;
    return TRUE;
}

BOOL ARCCloseDir( ARCDir *dir )
{
#pragma unused( dir )
    return TRUE;
}
