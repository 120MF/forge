#include "build.hpp"

#include "CMakeGenerator.hpp"
#include "TomlParser.hpp"

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

            generated_package = BuildSystem::parse_forge_toml(resolved_path);
            generator.generate_project(generated_package, std::filesystem::current_path() / "build");
        });
    }
}
