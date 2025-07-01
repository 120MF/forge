#include "CMakeGenerator.hpp"

#include <fstream>

#include "Package.hpp"
#include "Target.hpp"

namespace Forge::BuildSystem
{
    void CMakeGenerator::generate_project(const Core::Package& package, const std::filesystem::path& output_dir)
    {
        std::filesystem::create_directories(output_dir);
        const auto root_cmake = generate_root_cmakelists(package);
        write_file(output_dir / "CMakeLists.txt", root_cmake);
        for (const auto& target: package.targets)
        {
            auto target_dir = output_dir / target.src_dir;
            std::filesystem::create_directories(target_dir);
            auto target_cmake = generate_target_cmakelists(target);
            write_file(target_dir/"CMakeLists.txt", target_cmake);
        }
    }

    std::string CMakeGenerator::generate_root_cmakelists(const Core::Package& package)
    {
        std::ostringstream oss;
        oss << "cmake_minimum_required(VERSION 3.20)\n";
        oss << "project(" << package.name << " VERSION " << package.version.to_string() << ")\n\n";
        oss << "set(CMAKE_CXX_STANDARD 20)\n";
        oss << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n";

        for (const auto& target : package.targets) {
            oss << "add_subdirectory(" << target.src_dir << ")\n";
        }

        return oss.str();
    }

    std::string CMakeGenerator::generate_target_cmakelists(const Core::Target& target)
    {
        std::ostringstream oss;

        oss << "file(GLOB_RECURSE SOURCES \"*.cpp\" \"*.c\" \"*.cxx\")\n";
        oss << "file(GLOB_RECURSE HEADERS \"*.hpp\" \"*.h\" \"*.hxx\")\n\n";

        const std::string target_type = determine_target_type(target);
        if (target_type == "executable") {
            oss << "add_executable(" << target.name << " ${SOURCES})\n";
        } else {
            oss << "add_library(" << target.name << " ${SOURCES})\n";
        }

        if (!target.include_dir.empty()) {
            oss << "target_include_directories(" << target.name << " PUBLIC " << target.include_dir << ")\n";
        }

        return oss.str();
    }

    std::string CMakeGenerator::determine_target_type(const Core::Target& target)
    {
        if (target.target_type == "bin" || target.target_type == "executable") {
            return "executable";
        }
        return "library";
    }

    void CMakeGenerator::write_file(const std::filesystem::path& path, const std::string& content)
    {
        std::ofstream file(path);
        if (!file) {
            throw std::runtime_error("Failed to write file: " + path.string());
        }
        file << content;
    }
}
