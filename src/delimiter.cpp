#include "gbopt/delimiter.hpp"
#include <algorithm>
#include <iterator>

namespace gbopt
{

auto operator==(char lhs, CommaOrWhiteSpaceDelimiter const& rhs) noexcept
    -> bool
{
    return std::any_of(std::begin(rhs.kValues),
                       std::end(rhs.kValues),
                       [&](auto const& v) { return v == lhs; });
}

auto operator!=(char lhs, CommaOrWhiteSpaceDelimiter const& rhs) noexcept
    -> bool
{
    return !(lhs == rhs);
}

auto operator==(CommaOrWhiteSpaceDelimiter const& lhs, char rhs) noexcept
    -> bool
{
    return rhs == lhs;
}

auto operator!=(CommaOrWhiteSpaceDelimiter const& lhs, char rhs) noexcept
    -> bool
{
    return !(rhs == lhs);
}

} // namespace gbopt
