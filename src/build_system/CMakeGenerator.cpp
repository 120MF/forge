#include "CMakeGenerator.hpp"
#include "BuildConfig.hpp"

#include <format>
#include <fstream>

#include "Package.hpp"
#include "Target.hpp"

namespace Forge::BuildSystem
{
    void CMakeGenerator::generate_project(const Core::Package& package, const BuildConfig& config)
    {
        auto actual_build_dir = config.cache_dir / "build";
        std::filesystem::create_directories(actual_build_dir);
        const auto root_cmake = generate_root_cmakelists(package);
        write_file(actual_build_dir / "CMakeLists.txt", root_cmake);
        for (const auto& target : package.targets)
        {
            auto target_dir = actual_build_dir / target.src_dir;
            std::filesystem::create_directories(target_dir);
            auto target_cmake = generate_target_cmakelists(target, config.project_root);
            write_file(target_dir / "CMakeLists.txt", target_cmake);
        }
        std::filesystem::remove_all(config.build_dir);
        std::filesystem::create_symlink(actual_build_dir, config.build_dir);
    }

    std::string CMakeGenerator::generate_root_cmakelists(const Core::Package& package)
    {
        std::string content = std::format(
            "cmake_minimum_required(VERSION 3.20)\n"
            "project({} VERSION {})\n\n"
            "set(CMAKE_CXX_STANDARD 20)\n"
            "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n",
            package.name,
            package.version.to_string()
        );
        for (const auto& target : package.targets)
        {
            content += std::format("add_subdirectory({})\n", target.src_dir.string());
        }
        return content;
    }

    std::string CMakeGenerator::generate_target_cmakelists(const Core::Target& target,
                                                           const std::filesystem::path& project_root)
    {
        const auto source_dir = project_root / target.src_dir;
        std::string content = std::format(
            "file(GLOB_RECURSE SOURCES \"{}/*.cpp\" \"{}/*.c\" \"{}/*.cxx\")\n"
            "file(GLOB_RECURSE HEADERS \"{}/*.hpp\" \"{}/*.h\" \"{}/*.hxx\")\n\n",
            source_dir.string(), source_dir.string(), source_dir.string(),
            source_dir.string(), source_dir.string(), source_dir.string()
        );

        if (const std::string target_type = determine_target_type(target); target_type == "executable")
        {
            content += std::format("add_executable({} ${{SOURCES}})\n", target.name);
        }
        else
        {
            content += std::format("add_library({} ${{SOURCES}})\n", target.name);
        }

        if (!target.include_dir.empty())
        {
            content += std::format("target_include_directories({} PUBLIC {})\n",
                                   target.name,
                                   target.include_dir.string());
        }

        for (auto dep : target.dependencies)
        {
            content += std::format("target_link_libraries({} PRIVATE {})\n",
                                   target.name,
                                   dep.name
            );
        }

        return content;
    }

    std::string CMakeGenerator::determine_target_type(const Core::Target& target)
    {
        if (target.target_type == "exe" || target.target_type == "executable")
        {
            return "executable";
        }
        return "library";
    }

    void CMakeGenerator::write_file(const std::filesystem::path& path, const std::string& content)
    {
        std::ofstream file(path);
        if (!file)
        {
            throw std::runtime_error("Failed to write file: " + path.string());
        }
        file << content;
    }
}
