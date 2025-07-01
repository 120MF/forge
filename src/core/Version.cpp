#include "Version.hpp"

#include <sstream>

namespace Forge::Core
{
    Version::Version(const std::string& versionStr)
    {
        std::stringstream ss(versionStr);
        char dot;
        ss >> major >> dot >> minor >> dot >> patch;
    }

    auto Version::to_tuple() const noexcept
    {
        return std::tie(major, minor, patch);
    }

    auto Version::to_string() const noexcept
    {
        return std::format("{}.{}.{}", major, minor, patch);
    }
}
