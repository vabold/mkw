#ifndef EGG_THREAD_H
#define EGG_THREAD_H

#include <egg/core/eggHeap.h>

namespace EGG
{

class Thread
{
public:
    static Thread *findThread( OSThread *thread );

    /******************************************************************************
     *
     * Header-defined functions
     *
     ******************************************************************************/

    Heap *getNewHeap( void ) const
    {
        return mNewHeap;
    }

private:
    u8 _00[ 0x3c - 0x00 ];
    Heap *mNewHeap;
};

} // namespace EGG

#endif // EGG_THREAD_H
