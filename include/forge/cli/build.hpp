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
        bool run_cmake_configure(const BuildSystem::BuildConfig& config);
        bool run_cmake_build(const BuildSystem::BuildConfig& config);
        ::CLI::App* build_command;
        std::string target_path_str{};
        BuildSystem::CMakeGenerator generator;
        Core::Package generated_package;
    };
};


#endif //BUILD_HPP
