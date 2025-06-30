#ifndef FORGETARGET_HPP
#define FORGETARGET_HPP
#include <filesystem>

namespace Forge::Core
{
    struct Target
    {
        Target() = default;
        std::string name{};
        std::filesystem::path src_dir{};
        std::filesystem::path include_dir{};
        std::string target_type{};
    };
}

#endif //FORGETARGET_HPP
