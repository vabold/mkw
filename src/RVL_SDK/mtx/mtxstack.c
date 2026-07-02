#include <RVL_SDK/mtx.h>
#include <RVL_SDK/mtx/internal/mtxAssert.h>
#include <RVL_SDK/os.h>

#define STACK_OVERFLOW_CHECK( sPtr ) \
    ( u32 )( ( sPtr->stackPtr - sPtr->stackBase ) / 3 ) >= sPtr->numMtx - 1

void MTXInitStack( MtxStackPtr sPtr, u32 numMtx )
{
    OSAssertMessage( sPtr, "MTXInitStack():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase,
            "MTXInitStack():  'sPtr' contains a NULL ptr to stack memory " );
    OSAssertMessage( numMtx != 0, "MTXInitStack():  'numMtx' is 0 " );

    sPtr->numMtx = numMtx;
    sPtr->stackPtr = NULL;
}

MtxPtr MTXPush( MtxStackPtr sPtr, CMtxPtr m )
{
    OSAssertMessage( sPtr, "MTXPush():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase, "MTXPush():  'sPtr' contains a NULL ptr to stack memory " );
    OSAssertMessage( m, "MTXPush():  NULL MtxPtr 'm' " );

    if( sPtr->stackPtr == NULL )
    {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy( m, sPtr->stackPtr );
    }
    else
    {
        if( STACK_OVERFLOW_CHECK( sPtr ) )
        {
            OSAssertMessage( FALSE, "MTXPush():  stack overflow " );
        }

        MTXCopy( m, sPtr->stackPtr + 3 );
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPushFwd( MtxStackPtr sPtr, CMtxPtr m )
{
    OSAssertMessage( sPtr, "MTXPushFwd():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase,
            "MTXPushFwd():  'sPtr' contains a NULL ptr to stack memory " );
    OSAssertMessage( m, "MTXPushFwd():  NULL MtxPtr 'm' " );

    if( sPtr->stackPtr == NULL )
    {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy( m, sPtr->stackPtr );
    }
    else
    {
        if( STACK_OVERFLOW_CHECK( sPtr ) )
        {
            OSAssertMessage( FALSE, "MTXPushFwd():  stack overflow" );
        }

        MTXConcat( sPtr->stackPtr, m, sPtr->stackPtr + 3 );
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPushInv( MtxStackPtr sPtr, CMtxPtr m )
{
    Mtx inv;

    OSAssertMessage( sPtr, "MTXPushInv():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase,
            "MTXPushInv():  'sPtr' contains a NULL ptr to stack memory " );
    OSAssertMessage( m, "MTXPushInv():  NULL MtxPtr 'm' " );

    MTXInverse( m, inv );

    if( sPtr->stackPtr == NULL )
    {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy( inv, sPtr->stackPtr );
    }
    else
    {
        if( STACK_OVERFLOW_CHECK( sPtr ) )
        {
            OSAssertMessage( FALSE, "MTXPushInv():  stack overflow" );
        }

        MTXConcat( inv, sPtr->stackPtr, sPtr->stackPtr + 3 );
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPushInvXpose( MtxStackPtr sPtr, CMtxPtr m )
{
    Mtx invXpose;

    OSAssertMessage( sPtr, "MTXPushInvXpose():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase,
            "MTXPushInvXpose():  'sPtr' contains a NULL ptr to stack memory " );
    OSAssertMessage( m, "MTXPushInvXpose():  NULL MtxPtr 'm' " );

    MTXInverse( m, invXpose );
    MTXTranspose( invXpose, invXpose );

    if( sPtr->stackPtr == NULL )
    {
        sPtr->stackPtr = sPtr->stackBase;
        MTXCopy( invXpose, sPtr->stackPtr );
    }
    else
    {
        if( STACK_OVERFLOW_CHECK( sPtr ) )
        {
            OSAssertMessage( FALSE, "MTXPushInvXpose():  stack overflow " );
        }

        MTXConcat( sPtr->stackPtr, invXpose, sPtr->stackPtr + 3 );
        sPtr->stackPtr += 3;
    }

    return sPtr->stackPtr;
}

MtxPtr MTXPop( MtxStackPtr sPtr )
{
    OSAssertMessage( sPtr, "MTXPop():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase, "MTXPop():  'sPtr' contains a NULL ptr to stack memory " );

    if( sPtr->stackPtr == NULL )
    {
        return NULL;
    }

    if( sPtr->stackBase == sPtr->stackPtr )
    {
        sPtr->stackPtr = NULL;
        return NULL;
    }

    sPtr->stackPtr -= 3;
    return sPtr->stackPtr;
}

MtxPtr MTXGetStackPtr( MtxStackPtr sPtr )
{
    OSAssertMessage( sPtr, "MTXGetStackPtr():  NULL MtxStackPtr 'sPtr' " );
    OSAssertMessage( sPtr->stackBase,
            "MTXGetStackPtr():  'sPtr' contains a NULL ptr to stack memory " );
    return sPtr->stackPtr;
}
