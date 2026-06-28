#include <nw4r/ut/binaryFileFormat.h>

namespace nw4r
{
namespace ut
{

bool IsValidBinaryFile( const BinaryFileHeader *header, u32 signature, u16 version, u16 minBlocks )
{
    if( header->signature != signature )
    {
        return false;
    }

    if( header->byteOrder != 0xfeff )
    {
        return false;
    }

    if( header->version != version )
    {
        return false;
    }

    if( header->fileSize < minBlocks * sizeof( BinaryBlockHeader ) + sizeof( BinaryFileHeader ) )
    {
        return false;
    }

    // Debug has a warning here, so it's not returning dataBlocks >= minBlocks
    if( header->dataBlocks < minBlocks )
    {
        return false;
    }

    return true;
}

} // namespace ut
} // namespace nw4r
