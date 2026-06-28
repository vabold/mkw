#include <nw4r/ut/list.h>

#define GET_LINK( list, object ) ( (Link *)( (u8 *)( object ) + list->offset ) )

namespace nw4r
{
namespace ut
{

void List_Init( List *list, u16 offset )
{
    list->headObject = NULL;
    list->tailObject = NULL;
    list->numObjects = 0;
    list->offset = offset;
}

static void SetFirstObject( List *list, void *object )
{
    Link *link = GET_LINK( list, object );

    link->nextObject = NULL;
    link->prevObject = NULL;

    list->headObject = object;
    list->tailObject = object;

    ++list->numObjects;
}

void List_Append( List *list, void *object )
{
    if( !list->headObject )
    {
        SetFirstObject( list, object );
        return;
    }

    Link *link = GET_LINK( list, object );
    link->prevObject = list->tailObject;
    link->nextObject = NULL;

    GET_LINK( list, list->tailObject )->nextObject = object;
    list->tailObject = object;

    ++list->numObjects;
}

void List_Prepend( List *list, void *object )
{
    if( !list->headObject )
    {
        SetFirstObject( list, object );
        return;
    }

    Link *link = GET_LINK( list, object );
    link->prevObject = NULL;
    link->nextObject = list->headObject;

    GET_LINK( list, list->headObject )->prevObject = object;
    list->headObject = object;

    ++list->numObjects;
}

void List_Insert( List *list, void *target, void *object )
{
    if( !target )
    {
        List_Append( list, object );
        return;
    }

    if( target == list->headObject )
    {
        List_Prepend( list, object );
        return;
    }

    Link *link = GET_LINK( list, object );
    void *prevObj = GET_LINK( list, target )->prevObject;
    Link *prevLnk = GET_LINK( list, prevObj );

    link->prevObject = prevObj;
    link->nextObject = target;

    prevLnk->nextObject = object;
    GET_LINK( list, target )->prevObject = object;

    ++list->numObjects;
}

void List_Remove( List *list, void *object )
{
    Link *link = GET_LINK( list, object );

    if( !link->prevObject )
    {
        list->headObject = link->nextObject;
    }
    else
    {
        GET_LINK( list, link->prevObject )->nextObject = link->nextObject;
    }

    if( !link->nextObject )
    {
        list->tailObject = link->prevObject;
    }
    else
    {
        GET_LINK( list, link->nextObject )->prevObject = link->prevObject;
    }

    link->prevObject = NULL;
    link->nextObject = NULL;
    --list->numObjects;
}

void *List_GetNext( const List *list, const void *object )
{
    return !object ? list->headObject : GET_LINK( list, object )->nextObject;
}

void *List_GetPrev( const List *list, const void *object )
{
    return !object ? list->tailObject : GET_LINK( list, object )->prevObject;
}

void *List_GetNth( const List *list, u16 n )
{
    int i = 0;
    for( void *object = NULL; object = List_GetNext( list, object ); ++i )
    {
        if( n == i )
        {
            return object;
        }
    }

    return NULL;
}

} // namespace ut
} // namespace nw4r
