#include "build.hpp"
#include "CMakeGenerator.hpp"
#include "TomlParser.hpp"

#include <fmt/color.h>

namespace Forge::CLI
{
    BuildCommand::BuildCommand(::CLI::App& app)
    {
        build_command = app.add_subcommand("build", "Build the project");
        build_command->add_option("target", target_path, "Build target path")->default_val(".");
        build_command->callback([this]
        {
            std::filesystem::path resolved_path = target_path;
            if (resolved_path == ".")
            {
                resolved_path = "./forge.toml";
            }
            resolved_path = std::filesystem::current_path() / resolved_path;

            auto generated_package = BuildSystem::parse_forge_toml(resolved_path);
            if (generated_package)
            {
                BuildSystem::CMakeGenerator::generate_project(generated_package.value(),
                                                              std::filesystem::current_path() / "build");
                fmt::print(fg(fmt::color::green), "✓ Build successful!\n");
            }
            else
            {
                fmt::print(fg(fmt::color::red), "✗ Error: {}\n", generated_package.error().message);
            }
        });
    }
}
