#ifndef BUILDCONFIG_HPP
#define BUILDCONFIG_HPP
#include <filesystem>

namespace Forge::BuildSystem
{
    struct BuildConfig
    {
        std::filesystem::path build_dir;
        std::filesystem::path project_root;
    };
}
#endif //BUILDCONFIG_HPP
