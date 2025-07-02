#ifndef BUILDCONFIG_HPP
#define BUILDCONFIG_HPP
#include <filesystem>

namespace Forge::BuildSystem
{
    struct BuildConfig
    {
        std::filesystem::path project_root;
        std::filesystem::path cache_dir;
        std::filesystem::path build_dir;
    };
}
#endif //BUILDCONFIG_HPP
