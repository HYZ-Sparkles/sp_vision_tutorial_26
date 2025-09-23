#include <iostream>
#include <fmt/core.h>

int main()
{
    std::string s=fmt::format("My name is {},my age is {}\n","Jack",20);
    std::cout<<s;
    fmt::print("I don't like {}\n","banana");

    return 0;
}