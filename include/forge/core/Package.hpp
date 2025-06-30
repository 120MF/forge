#ifndef FORGEPACKAGE_HPP
#define FORGEPACKAGE_HPP

#include <string>
#include <unordered_set>

#include "Target.hpp"
#include "Version.hpp"

namespace Forge::Core
{
    struct Package
    {
        std::string name{};
        std::string description{};
        Version version{};
        std::unordered_set<std::string> authors{};
        std::string license{};
        std::string repository{};

        std::unordered_set<Target> targets{};

        Package() = default;
    };
}

#endif //FORGEPACKAGE_HPP
