#include "Version.hpp"

#include <sstream>

Forge::Version::Version(const std::string& versionStr)
{
    std::stringstream ss(versionStr);
    char dot;
    ss >> major >> dot >> minor >> dot >> patch;
}

auto Forge::Version::to_tuple() const noexcept
{
    return std::tie(major, minor, patch);
}
