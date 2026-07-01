#ifndef NW4R_UT_INLINES_H
#define NW4R_UT_INLINES_H

namespace nw4r
{
namespace ut
{
namespace
{

class NonCopyable
{
public:
    NonCopyable( void ) { }
    ~NonCopyable( void ) { }

private:
    NonCopyable( const NonCopyable &rhs );
    NonCopyable &operator=( const NonCopyable &rhs );
};

} // namespace
} // namespace ut
} // namespace nw4r

#endif
