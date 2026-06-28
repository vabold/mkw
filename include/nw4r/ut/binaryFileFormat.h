#ifndef NW4R_UT_BINARYFILEFORMAT_H
#define NW4R_UT_BINARYFILEFORMAT_H

#include <RVL_SDK/types.h>

namespace nw4r
{
namespace ut
{

struct BinaryFileHeader
{
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
};

struct BinaryBlockHeader
{
    u32 kind;
    u32 size;
};

bool IsValidBinaryFile( const BinaryFileHeader *header, u32 signature, u16 version, u16 minBlocks );

} // namespace ut
} // namespace nw4r

#endif
