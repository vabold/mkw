#ifndef EGG_HEAP_H
#define EGG_HEAP_H

#include <egg/core/eggDisposer.h>

namespace EGG
{

class Heap
{
public:
    void appendDisposer( Disposer *disposer )
    {
        nw4r::ut::List_Append( &mChildren, disposer );
    }

    void removeDisposer( Disposer *disposer )
    {
        nw4r::ut::List_Remove( &mChildren, disposer );
    }

    static Heap *findContainHeap( const void *memBlock );

private:
    u8 _00[ 0x28 - 0x00 ];
    nw4r::ut::List mChildren;
    u8 _34[ 0x38 - 0x34 ];
};

} // namespace EGG

#endif
