#ifndef FORGE_TOMLPARSER_HPP
#define FORGE_TOMLPARSER_HPP

#include <expected>
#include <filesystem>

namespace Forge::Core
{
    struct Package;
}

namespace Forge::BuildSystem
{
    enum class ParseErrorType
    {
        FileNotFound,
        TomlSyntaxError,
        MissingPackageSection,
        InvalidPackageVersion,
        InvalidTargetDefinition,
        InvalidDependencyDefinition,
    };

    struct ParseError
    {
        ParseErrorType type;
        std::string message;
        std::filesystem::path file_path;

        ParseError(const ParseErrorType t, std::string msg, std::filesystem::path path = {}) :
            type(t), message(std::move(msg)), file_path(std::move(path))
        {
        }
    };

    std::expected<Core::Package, ParseError> parse_forge_toml(const std::filesystem::path& toml_path);
}

#endif //FORGE_TOMLPARSER_HPP
