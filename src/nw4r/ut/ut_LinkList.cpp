#include <nw4r/ut/LinkList.h>

namespace nw4r
{
namespace ut
{
namespace detail
{

LinkListImpl::~LinkListImpl( void )
{
    Clear( );
}

LinkListImpl::Iterator LinkListImpl::Erase( Iterator it )
{
    Iterator itNext = it;
    return Erase( it, ++itNext );
}

// Erases all nodes including/after the first iterator and before the last iterator
LinkListImpl::Iterator LinkListImpl::Erase( Iterator itFirst, Iterator itLast )
{
    LinkListNode *pIt = itFirst.mPointer;
    LinkListNode *const pItLast = itLast.mPointer;
    LinkListNode *pNext;

    while( pIt != pItLast )
    {
        pNext = pIt->GetNext( );
        Erase( pIt );
        pIt = pNext;
    }

    return itLast;
}

void LinkListImpl::Clear( void )
{
    Erase( GetBeginIter( ), GetEndIter( ) );
}

void LinkListImpl::Reverse( void )
{
    if( IsEmpty( ) )
    {
        return;
    }

    LinkListNode *p = mNode.mNext;
    LinkListNode *pNext;

    Initialize_( );

    // All of the links are still linked to each other in their original order
    // This includes the end link pointing to the list node to mark the end iterator
    // Just reattach them to the list in a different order
    while( p != &mNode )
    {
        pNext = p->mNext;
        // Insertion requires delinking first
        p->mNext = NULL;
        p->mPrev = NULL;
        PushFront( p );
        p = pNext;
    }
}

// Inserts the node before the iterator
LinkListImpl::Iterator LinkListImpl::Insert( Iterator it, LinkListNode *p )
{
    // The node should always be non-NULL
    // The iterator should always have a non-NULL node
    // The iterator's prev should always be non-NULL
    // The node should always be unlinked
    LinkListNode *const pIt = it.mPointer;
    LinkListNode *const pItPrev = pIt->mPrev;

    p->mNext = pIt;
    p->mPrev = pItPrev;
    pIt->mPrev = p;
    pItPrev->mNext = p;
    ++mSize;
    return Iterator( p );
}

LinkListImpl::Iterator LinkListImpl::Erase( LinkListNode *p )
{
    // The list shouldn't be empty
    // The node should always be non-NULL
    // The node should never be mNode
    // pNext and pPrev should always be non-NULL
    LinkListNode *const pNext = p->mNext;
    LinkListNode *const pPrev = p->mPrev;

    pNext->mPrev = pPrev;
    pPrev->mNext = pNext;
    --mSize;
    p->mNext = NULL;
    p->mPrev = NULL;
    return Iterator( pNext );
}

} // namespace detail
} // namespace ut
} // namespace nw4r
