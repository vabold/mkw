#ifndef EGG_DISPOSER_H
#define EGG_DISPOSER_H

#include <nw4r/ut/list.h>

namespace EGG
{

class Heap;

class Disposer
{
public:
    Disposer( void );
    virtual ~Disposer( void );

private:
    Heap *mHeap;
    nw4r::ut::Link mLink;
};

} // namespace EGG

#endif
