#include "build.hpp"
#include "CMakeGenerator.hpp"
#include "TomlParser.hpp"

#include <fmt/color.h>
#include <cstdlib>
#include <sstream>
#include <thread>

#include "BuildConfig.hpp"

namespace Forge::CLI
{
    BuildCommand::BuildCommand(::CLI::App& app)
    {
        build_command = app.add_subcommand("build", "Build the project");
        build_command->add_option("target", target_path_str, "Build target path");
        build_command->callback([this]
        {
            std::filesystem::path resolved_path;
            if (target_path_str.empty())
            {
                resolved_path = std::move(std::filesystem::current_path());
            }
            else
            {
                resolved_path = std::move(target_path_str);
            }

            auto generated_package = BuildSystem::parse_forge_toml(resolved_path / "forge.toml");
            if (generated_package)
            {
                const BuildSystem::BuildConfig config{
                    .build_dir = std::move(resolved_path / "build"),
                    .project_root = std::move(resolved_path),
                };
                BuildSystem::CMakeGenerator::generate_project(generated_package.value(),
                                                              config);
                if (run_cmake_configure(config) && run_cmake_build(config))
                {
                    fmt::print(fg(fmt::color::green), "✓ Build successful!\n");
                }
                else
                {
                    fmt::print(fg(fmt::color::red), "✗ Build failed!\n");
                }
            }
            else
            {
                fmt::print(fg(fmt::color::red), "✗ Error: {}\n", generated_package.error().message);
            }
        });
    }

    bool BuildCommand::run_cmake_configure(const BuildSystem::BuildConfig& config)
    {
        try
        {
            std::filesystem::create_directories(config.build_dir);
            fmt::print(fmt::fg(fmt::color::blue), "🔧 Configuring with CMake...\n"
                       "Folder: {}\n", config.build_dir.string());
            const auto current_dir = std::filesystem::current_path();
            std::filesystem::current_path(config.build_dir);
            int result = std::system("cmake .");

            std::filesystem::current_path(current_dir);
            if (result != 0)
            {
                fmt::print(fg(fmt::color::red), "✗ CMake configure failed with exit code: {}\n", result);
                return false;
            }
            fmt::print(fg(fmt::color::green), "✓ CMake configure completed\n");
            return true;
        }
        catch (const std::exception& e)
        {
            fmt::print(fg(fmt::color::red), "✗ CMake configure error: {}\n", e.what());
            return false;
        }
    }

    bool BuildCommand::run_cmake_build(const BuildSystem::BuildConfig& config)
    {
        try
        {
            fmt::print(fg(fmt::color::blue), "🔨 Building with CMake...\n");
            const auto current_dir = std::filesystem::current_path();

            std::filesystem::current_path(config.build_dir);
            std::ostringstream build_cmd;
            build_cmd << "cmake --build . --config Release";
            if (const auto num_cores = std::thread::hardware_concurrency(); num_cores > 0)
            {
                build_cmd << " -j" << num_cores;
            }
            else
            {
                build_cmd << " -j";
            }
            int result = std::system(build_cmd.str().c_str());

            std::filesystem::current_path(current_dir);

            if (result != 0)
            {
                fmt::print(fg(fmt::color::red), "✗ CMake build failed with exit code: {}\n", result);
                return false;
            }

            fmt::print(fg(fmt::color::green), "✓ CMake build completed\n");
            return true;
        }
        catch (const std::exception& e)
        {
            fmt::print(fg(fmt::color::red), "✗ CMake build error: {}\n", e.what());
            return false;
        }
    }
}
