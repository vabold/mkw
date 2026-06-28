#ifndef NW4R_UT_LIST_H
#define NW4R_UT_LIST_H

#include <RVL_SDK/types.h>

namespace nw4r
{
namespace ut
{

struct List
{
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
};

struct Link
{
    void *prevObject;
    void *nextObject;
};

void List_Init( List *list, u16 offset );
void List_Append( List *list, void *object );
void List_Insert( List *list, void *target, void *object );
void List_Remove( List *list, void *object );
void *List_GetNext( const List *list, const void *object );
void *List_GetPrev( const List *list, const void *object );
void *List_GetNth( const List *list, u16 n );

} // namespace ut
} // namespace nw4r

#endif
