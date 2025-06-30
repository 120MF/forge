#ifndef FORGE_TOMLPARSER_HPP
#define FORGE_TOMLPARSER_HPP
#include "Package.hpp"

namespace Forge::Core
{
    Package parse_forge_toml(const std::filesystem::path& toml_path);
}

#endif //FORGE_TOMLPARSER_HPP
