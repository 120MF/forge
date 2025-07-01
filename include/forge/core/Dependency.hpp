#ifndef DEPENDENCY_HPP
#define DEPENDENCY_HPP
#include <optional>
#include <string>
#include <vector>

#include "Version.hpp"

namespace Forge::Core
{
    struct Dependency
    {
        std::string name;
        std::optional<Version> version;
        std::optional<std::string> git;
        std::optional<std::string> tag;
        std::optional<std::vector<std::string>> target_names;
        std::optional<std::string> type;
    };
}

#endif //DEPENDENCY_HPP
