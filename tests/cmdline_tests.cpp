#include "gbopt/cmdline.hpp"
#include "testing.hpp"
#include <span>
#include <string_view>
#include <vector>

enum class Flags
{
    show_version,
    output_metrics,
    print_fan_curve,
    interval_length,
    quiet,
    silent,
    verbose,
    print_help,
    no_pidfile,
    max_temperature,
    force,
    persistence_mode,
};

gbopt::FlagDefinition<Flags> const flag_defs[] = {
    { Flags::show_version, 'v', "version", gbopt::FlagArgument::none },
    { Flags::interval_length,
      'n',
      "interval-length",
      gbopt::FlagArgument::required,
      {},
      gbopt::validation::in_integer_range<Flags>(1, 5) },
    { Flags::quiet,
      'q',
      "quiet",
      gbopt::FlagArgument::none,
      { Flags::silent, Flags::verbose } },
    { Flags::silent,
      0,
      "silent",
      gbopt::FlagArgument::none,
      { Flags::quiet, Flags::verbose } },
    { Flags::verbose,
      0,
      "verbose",
      gbopt::FlagArgument::none,
      { Flags::quiet, Flags::silent } },
    { Flags::output_metrics, 'o', "output-metrics", gbopt::FlagArgument::none },
    { Flags::print_fan_curve,
      'p',
      "print-fan-curve",
      gbopt::FlagArgument::none },
    { Flags::print_help, 'h', "help", gbopt::FlagArgument::none },
    { Flags::no_pidfile, 0, "no-pidfile", gbopt::FlagArgument::none },
    { Flags::max_temperature,
      0,
      "max-temperature",
      gbopt::FlagArgument::required,
      {},
      gbopt::validation::is_integer<Flags>() },
    { Flags::force, 0, "force", gbopt::FlagArgument::none },
    { Flags::persistence_mode,
      'P',
      "persistence-mode",
      gbopt::FlagArgument::none,
      { Flags::print_fan_curve } },
};

auto should_parse_cmdline_with_no_args() -> void
{
    auto const cmdline =
        gbopt::parse_cmdline({ static_cast<char const**>(nullptr), 0 });

    EXPECT(cmdline.args().size() == 0);
    EXPECT(cmdline.flags().size() == 0);
}

auto should_parse_cmdline() -> void
{
    using namespace std::string_literals;
    using namespace std::literals::string_view_literals;

    char const* argv[] { "one", "-v",    "two", "--interval-length",
                         "5",   "three", "-v",  "-",
                         "--",  "exec",  "-V",  nullptr };
    int argc = static_cast<int>(std::size(argv));

    std::span<gbopt::FlagDefinition<Flags> const> defs { flag_defs };
    auto const cmdline =
        gbopt::parse_cmdline({ argv, static_cast<std::size_t>(argc) }, defs);

    EXPECT(cmdline.args().size() == 6);
    EXPECT("one"sv == std::string_view { cmdline.args()[0] });
    EXPECT("two"sv == std::string_view { cmdline.args()[1] });
    EXPECT("three"sv == std::string_view { cmdline.args()[2] });
    EXPECT("-"sv == std::string_view { cmdline.args()[3] });
    EXPECT("exec"sv == std::string_view { cmdline.args()[4] });
    EXPECT("-V"sv == std::string_view { cmdline.args()[5] });
    EXPECT(cmdline.flags().size() == 3);
    EXPECT(std::get<0>(cmdline.flags()[0]) == Flags::show_version);
    EXPECT(std::get<1>(cmdline.flags()[0]) == std::nullopt);
    EXPECT(std::get<0>(cmdline.flags()[1]) == Flags::interval_length);
    EXPECT(std::get<1>(cmdline.flags()[1]) != std::nullopt);
    EXPECT(*std::get<1>(cmdline.flags()[1]) == "5"sv);
}

auto should_parse_cmdline_with_no_flag_defs() -> void
{
    using namespace std::string_literals;
    using namespace std::literals::string_view_literals;

    char const* argv[] { "one", "two", "three", "--", "exec" };
    int argc = static_cast<int>(std::size(argv));

    auto const cmdline =
        gbopt::parse_cmdline({ argv, static_cast<std::size_t>(argc) });

    EXPECT(cmdline.args().size() == 4);
    EXPECT("one"sv == std::string_view { cmdline.args()[0] });
    EXPECT("two"sv == std::string_view { cmdline.args()[1] });
    EXPECT("three"sv == std::string_view { cmdline.args()[2] });
    EXPECT("exec"sv == std::string_view { cmdline.args()[3] });
    EXPECT(cmdline.flags().size() == 0);
}

auto should_print_options() -> void { gbopt::print_flag_defs(flag_defs); }

auto main() -> int
{
    return testing::run({ TEST(should_parse_cmdline_with_no_args),
                          TEST(should_parse_cmdline),
                          TEST(should_parse_cmdline_with_no_flag_defs),
                          TEST(should_print_options) });
}
