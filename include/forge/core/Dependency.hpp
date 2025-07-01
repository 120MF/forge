#ifndef DEPENDENCY_HPP
#define DEPENDENCY_HPP
#include <optional>
#include <string>
#include <vector>

namespace Forge::Core
{
    struct Dependency
    {
        std::string name;
        std::optional<std::string> version;
        std::optional<std::string> git;
        std::optional<std::string> tag;
        std::optional<std::vector<std::string>> targets;
        std::optional<std::string> type;
    };
}

#endif //DEPENDENCY_HPP
