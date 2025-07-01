#include "Version.hpp"

#include <sstream>

namespace Forge::Core
{
    auto Version::to_tuple() const noexcept
    {
        return std::tie(major, minor, patch);
    }

    std::string Version::to_string() const noexcept
    {
        return std::format("{}.{}.{}", major, minor, patch);
    }
}
