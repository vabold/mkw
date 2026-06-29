#include <egg/core/eggDisposer.h>

#include <egg/core/eggHeap.h>

namespace EGG
{

Disposer::Disposer( void )
{
    mHeap = Heap::findContainHeap( this );
    if( mHeap )
    {
        mHeap->appendDisposer( this );
    }
}

Disposer::~Disposer( void )
{
    if( mHeap )
    {
        mHeap->removeDisposer( this );
    }
}

} // namespace EGG
