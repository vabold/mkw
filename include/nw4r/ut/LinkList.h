#ifndef NW4R_UT_LINKLIST_H
#define NW4R_UT_LINKLIST_H

#include <nw4r/ut/inlines.h>

#include <RVL_SDK/types.h>

namespace nw4r
{
namespace ut
{
namespace detail
{

// https://en.cppreference.com/cpp/iterator/iterator
template < class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T & >
struct Iterator
{
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

class LinkListImpl;

} // namespace detail

class LinkListNode : NonCopyable
{
    friend class detail::LinkListImpl;

public:
    LinkListNode( void ) : mNext( NULL ), mPrev( NULL ) { }
    ~LinkListNode( void ) { }

    LinkListNode *GetNext( void ) const
    {
        return mNext;
    }

    LinkListNode *GetPrev( void ) const
    {
        return mPrev;
    }

private:
    // NULL if unlinked, instantiated if linked

    LinkListNode *mNext;
    LinkListNode *mPrev;
};

namespace detail
{

// Manages a linked list of nodes
class LinkListImpl : NonCopyable
{
public:
    class ConstIterator;

    // Base iterator for a mutable node
    class Iterator : public detail::Iterator< LinkListNode >
    {
        friend class LinkListImpl;
        friend class ConstIterator;

    public:
        Iterator( void ) : mPointer( NULL ) { }
        Iterator( LinkListNode *p ) : mPointer( p ) { }

        // Copy constructor and destructor intentionally left implicitly defined
        // We don't get return value optimization otherwise

        Iterator &operator++( void )
        {
            mPointer = mPointer->GetNext( );
            return *this;
        }

        Iterator operator++( int )
        {
            Iterator it = *this;
            ++( *this );
            return it;
        }

        Iterator &operator--( void )
        {
            mPointer = mPointer->GetPrev( );
            return *this;
        }

        Iterator operator--( int )
        {
            Iterator it = *this;
            --( *this );
            return it;
        }

        LinkListNode *operator->( void ) const
        {
            return mPointer;
        }

        LinkListNode &operator*( void ) const
        {
            return *mPointer;
        }

        friend bool operator==( Iterator it1, Iterator it2 )
        {
            return it1.mPointer == it2.mPointer;
        }

        friend bool operator!=( Iterator it1, Iterator it2 )
        {
            return !( it1 == it2 );
        }

    private:
        LinkListNode *mPointer;
    };

    // Const iterator for an immutable node
    // NOTE: Keep the API as close as possible to the base iterator
    // NOTE: Iterator template args need to match type found in DWARF
    class ConstIterator
        : public detail::
                  Iterator< LinkListNode, ptrdiff_t, const LinkListNode *, const LinkListNode & >
    {
        friend class LinkListImpl;

    public:
        // The only way to make a const iterator is to promote a base iterator
        ConstIterator( LinkListImpl::Iterator it ) : mPointer( it.mPointer ) { }

        ConstIterator &operator++( void )
        {
            mPointer = mPointer->GetNext( );
            return *this;
        }

        ConstIterator operator++( int )
        {
            ConstIterator it = *this;
            ++( *this );
            return it;
        }

        ConstIterator &operator--( void )
        {
            mPointer = mPointer->GetPrev( );
            return *this;
        }

        ConstIterator operator--( int )
        {
            ConstIterator it = *this;
            --( *this );
            return it;
        }

        const LinkListNode *operator->( void ) const
        {
            return mPointer;
        }

        const LinkListNode &operator*( void ) const
        {
            return *mPointer;
        }

        friend bool operator==( ConstIterator it1, ConstIterator it2 )
        {
            return it1.mPointer == it2.mPointer;
        }

        friend bool operator!=( ConstIterator it1, ConstIterator it2 )
        {
            return !( it1 == it2 );
        }

    private:
        const LinkListNode *mPointer;
    };

    LinkListImpl( void )
    {
        Initialize_( );
    }
    ~LinkListImpl( void );

    Iterator Erase( Iterator it );
    Iterator Erase( Iterator itFirst, Iterator itLast );
    void Clear( void );
    void Reverse( void );
    Iterator Insert( Iterator it, LinkListNode *p );
    Iterator Erase( LinkListNode *p );

    void Initialize_( void )
    {
        mSize = 0;
        mNode.mNext = &mNode;
        mNode.mPrev = &mNode;
    }

    void PopFront( void )
    {
        Erase( GetBeginIter( ) );
    }

    void PopBack( void )
    {
        Erase( GetEndIter( ) );
    }

    void PushFront( LinkListNode *p )
    {
        Insert( GetBeginIter( ), p );
    }

    void PushBack( LinkListNode *p )
    {
        Insert( GetEndIter( ), p );
    }

    Iterator GetBeginIter( void )
    {
        return Iterator( mNode.GetNext( ) );
    }

    ConstIterator GetBeginIter( void ) const
    {
        return ConstIterator( mNode.GetNext( ) );
    }

    Iterator GetEndIter( void )
    {
        return Iterator( &mNode );
    }

    ConstIterator GetEndIter( void ) const
    {
        // We need to const cast so the base iterator can be constructed
        // Promoting to ConstIterator ensures the node is kept const so this is safe
        return ConstIterator( const_cast< LinkListNode * >( &mNode ) );
    }

    u32 GetSize( void ) const
    {
        return mSize;
    }

    bool IsEmpty( void ) const
    {
        return mSize == 0;
    }

    static Iterator GetIteratorFromPointer( LinkListNode *p )
    {
        return Iterator( p );
    }

private:
    u32 mSize;
    // Nodes have NULL links if unlinked and instantiated links if linked
    // This node replaces NULL to delineate the head/tail of the list
    LinkListNode mNode;
};

} // namespace detail

// Manages a linked list of objects with exposed nodes
template < typename T, ptrdiff_t Offset >
class LinkList : detail::LinkListImpl
{
public:
    class ConstIterator;

    // Iterator for a mutable object
    class Iterator : public detail::Iterator< T >
    {
        friend class ConstIterator;

    public:
        Iterator( void ) { }
        Iterator( detail::LinkListImpl::Iterator it ) : it_( it ) { }

        Iterator &operator++( void )
        {
            ++it_;
            return *this;
        }

        Iterator operator++( int )
        {
            Iterator it = *this;
            ++( *this );
            return it;
        }

        Iterator &operator--( void )
        {
            --it_;
            return *this;
        }

        Iterator operator--( int )
        {
            Iterator it = *this;
            --( *this );
            return it;
        }

        T *operator->( void ) const
        {
            return GetPointerFromNode( it_.operator->( ) );
        }

        T &operator*( void ) const
        {
            return *operator->( );
        }

        friend bool operator==( Iterator it1, Iterator it2 )
        {
            return it1.it_ == it2.it_;
        }

        friend bool operator!=( Iterator it1, Iterator it2 )
        {
            return !( it1 == it2 );
        }

    private:
        detail::LinkListImpl::Iterator it_;
    };

    // Const iterator for an immutable node
    // NOTE: Keep the API as close as possible to the base iterator
    class ConstIterator : public detail::Iterator< T, ptrdiff_t, const T *, const T & >
    {
    public:
        // The only way to make a const iterator is to promote a base iterator
        ConstIterator( LinkList::Iterator it ) : it_( it.it_ ) { }

        ConstIterator &operator++( void )
        {
            ++it_;
            return *this;
        }

        ConstIterator operator++( int )
        {
            ConstIterator it = *this;
            ++( *this );
            return it;
        }

        ConstIterator &operator--( void )
        {
            --it_;
            return *this;
        }

        ConstIterator operator--( int )
        {
            ConstIterator it = *this;
            --( *this );
            return it;
        }

        const T *operator->( void ) const
        {
            return GetPointerFromNode( it_.operator->( ) );
        }

        const LinkListNode &operator*( void ) const
        {
            return *operator->( );
        }

        friend bool operator==( ConstIterator it1, ConstIterator it2 )
        {
            return it1.it_ == it2.it_;
        }

        friend bool operator!=( ConstIterator it1, ConstIterator it2 )
        {
            return !( it1 == it2 );
        }

    private:
        detail::LinkListImpl::ConstIterator it_;
    };

    LinkList( void ) { }
    ~LinkList( void ) { }

    Iterator Erase( Iterator it )
    {
        return Iterator( LinkListImpl::Erase( it.it_ ) );
    }

    Iterator Insert( Iterator it, T *p )
    {
        return Iterator( LinkListImpl::Insert( it.it_, GetNodeFromPointer( p ) ) );
    }

    Iterator Erase( T *p )
    {
        return Iterator( LinkListImpl::Erase( GetNodeFromPointer( p ) ) );
    }

    void PushFront( T *p )
    {
        Insert( GetBeginIter( ), p );
    }

    void PushBack( T *p )
    {
        Insert( GetBeginIter( ), p );
    }

    using LinkListImpl::PopBack;
    using LinkListImpl::PopFront;

    T &GetFront( void )
    {
        return *GetBeginIter( );
    }

    const T &GetFront( void ) const
    {
        return *GetBeginIter( );
    }

    T &GetBack( void )
    {
        return *--GetEndIter( );
    }

    const T &GetBack( void ) const
    {
        return *--GetEndIter( );
    }

    Iterator GetBeginIter( void )
    {
        return Iterator( LinkListImpl::GetBeginIter( ) );
    }

    ConstIterator GetBeginIter( void ) const
    {
        return ConstIterator( LinkListImpl::GetBeginIter( ) );
    }

    Iterator GetEndIter( void )
    {
        return Iterator( LinkListImpl::GetEndIter( ) );
    }

    ConstIterator GetEndIter( void ) const
    {
        return ConstIterator( LinkListImpl::GetEndIter( ) );
    }

    using LinkListImpl::GetSize;
    using LinkListImpl::IsEmpty;

    static T *GetPointerFromNode( LinkListNode *p )
    {
        return reinterpret_cast< T * >( reinterpret_cast< uintptr_t >( p ) - Offset );
    }

    static const T *GetPointerFromNode( const LinkListNode *p )
    {
        return reinterpret_cast< const T * >( reinterpret_cast< uintptr_t >( p ) - Offset );
    }

    static LinkListNode *GetNodeFromPointer( T *p )
    {
        return reinterpret_cast< LinkListNode * >( reinterpret_cast< uintptr_t >( p ) + Offset );
    }

    static const LinkListNode *GetNodeFromPointer( const T *p )
    {
        return reinterpret_cast< const LinkListNode * >(
                reinterpret_cast< uintptr_t >( p ) + Offset );
    }

    static Iterator GetIteratorFromPointer( LinkListNode *p )
    {
        return Iterator( LinkListImpl::GetIteratorFromPointer( p ) );
    }

    static ConstIterator GetIteratorFromPointer( const LinkListNode *p )
    {
        return ConstIterator( LinkListImpl::GetIteratorFromPointer( p ) );
    }

    static Iterator GetIteratorFromPointer( T *p )
    {
        return GetIteratorFromPointer( GetNodeFromPointer( p ) );
    }

    static ConstIterator GetIteratorFromPointer( const T *p )
    {
        return GetIteratorFromPointer( GetNodeFromPointer( p ) );
    }
};

} // namespace ut
} // namespace nw4r

#endif
