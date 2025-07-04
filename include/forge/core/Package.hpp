#ifndef FORGEPACKAGE_HPP
#define FORGEPACKAGE_HPP

#include <string>
#include <vector>
#include <unordered_set>

#include "Target.hpp"
#include "Version.hpp"

namespace Forge::Core
{
    struct Package
    {
        std::string name{};
        std::optional<std::string> description{};
        Version version{};
        std::optional<std::vector<std::string>> authors{};
        std::optional<std::string> license{};
        std::optional<std::string> repository{};

        std::vector<Target> targets{};

        Package() = default;
    };
}


#endif //FORGEPACKAGE_HPP
