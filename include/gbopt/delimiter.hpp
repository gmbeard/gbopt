#ifndef GBOPT_DELIMITER_HPP_INCLUDED
#define GBOPT_DELIMITER_HPP_INCLUDED

namespace gbopt
{

struct CommaOrWhiteSpaceDelimiter
{
    friend auto operator==(char lhs,
                           CommaOrWhiteSpaceDelimiter const& rhs) noexcept
        -> bool;

private:
    static constexpr char const kValues[] = { ',', ' ', '\r', '\n', '\t' };
};

auto operator==(char lhs, CommaOrWhiteSpaceDelimiter const& rhs) noexcept
    -> bool;

auto operator!=(char lhs, CommaOrWhiteSpaceDelimiter const& rhs) noexcept
    -> bool;

auto operator==(CommaOrWhiteSpaceDelimiter const& lhs, char rhs) noexcept
    -> bool;

auto operator!=(CommaOrWhiteSpaceDelimiter const& lhs, char rhs) noexcept
    -> bool;

} // namespace gbopt

#endif // GBOPT_DELIMITER_HPP_INCLUDED
