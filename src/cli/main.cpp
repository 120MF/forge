#include "CLI/CLI.hpp"
#include <print>

int main(int argc, char** argv)
{
    CLI::App app("Forge C++ Package Manager");
    app.set_version_flag("--version", std::string("0.1.0"));


    CLI11_PARSE(app, argc, argv);
    std::print("{}", app.get_description());
    return 0;
}
