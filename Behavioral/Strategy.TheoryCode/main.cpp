#include "strategy.hpp"

void canonical_usage_of_strategy()
{
    using namespace Canonical;

    Document data{std::make_shared<UpperCaseFormatter>()};
    data.pretty_print();

    auto lcf = std::make_shared<LowerCaseFormatter>();
    data.set_formatter(lcf);
    data.pretty_print();

    data.set_formatter(std::make_shared<CapitalizeFormatter>());
    data.pretty_print();
}

int main()
{
    using namespace ModernCpp;

    Document data{UpperCaseFormatter{}};
    data.pretty_print();

    LowerCaseFormatter lcf;
    data.set_formatter(lcf);
    data.pretty_print();

    data.set_formatter(CapitalizeFormatter{});
    data.pretty_print();
}
