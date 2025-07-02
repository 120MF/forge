#ifndef CMAKEGENERATOR_HPP
#define CMAKEGENERATOR_HPP
#include <filesystem>

namespace Forge::Core
{
    struct Target;
    struct Package;
}

namespace Forge::BuildSystem
{
    class CMakeGenerator
    {
    public:
        static void generate_project(const Core::Package& package, const struct BuildConfig& config);

    private:
        static std::string generate_root_cmakelists(const Core::Package& package);
        static std::string generate_target_cmakelists(const Core::Target& target,
                                                      const std::filesystem::path& project_root);
        static std::string determine_target_type(const Core::Target& target);
        static void write_file(const std::filesystem::path& path, const std::string& content);
    };
}

#endif //CMAKEGENERATOR_HPP
