#ifndef FORGETARGET_HPP
#define FORGETARGET_HPP
#include <filesystem>

namespace Forge
{
    struct Target
    {
        Target() = default;
        std::filesystem::path src_dir{};
        std::filesystem::path include_dir{};
    };
}

#endif //FORGETARGET_HPP
