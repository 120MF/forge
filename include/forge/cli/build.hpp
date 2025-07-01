#ifndef BUILD_HPP
#define BUILD_HPP

#include "CMakeGenerator.hpp"
#include "Package.hpp"
#include "CLI/CLI.hpp"

namespace Forge::CLI
{
    class BuildCommand
    {
    public:
        explicit BuildCommand(::CLI::App& app);

    private:
        ::CLI::App* build_command;
        std::filesystem::path target_path{"."};
        BuildSystem::CMakeGenerator generator;
        Core::Package generated_package;
    };
};


#endif //BUILD_HPP
