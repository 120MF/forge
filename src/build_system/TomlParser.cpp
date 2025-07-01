#include "TomlParser.hpp"

#include <ranges>
#include <toml++/toml.hpp>

#include "Dependency.hpp"
#include "Package.hpp"
using std::literals::operator ""s;
using enum Forge::BuildSystem::ParseErrorType;

namespace Forge::BuildSystem
{
    std::expected<Core::Version, ParseError> parse_version(std::string_view versionStr);
    std::expected<Core::Package, ParseError> parse_package(const parse_result& data);
    std::expected<Core::Target, ParseError> parse_target(const node_view<const node>& target_element);
    std::expected<Core::Dependency, ParseError> parse_dependency(node_view<const node>& node_view);

    std::expected<Core::Package, ParseError> parse_forge_toml(const std::filesystem::path& toml_path)
    {
        if (!std::filesystem::exists(toml_path))
        {
            return std::unexpected(ParseError{
                FileNotFound,
                std::format("forge.toml not found at: {}", toml_path.string())
            });
        }
        const auto data = parse_file(toml_path.string());
        if (data.succeeded())
        {
            return std::move(parse_package(data));
        }
        return std::unexpected(
            ParseError{TomlSyntaxError, std::format("Unexpected error: {}", data.error().description()), toml_path});
    }

    std::expected<Core::Package, ParseError> parse_package(const parse_result& data)
    {
        if (!data["package"].as_table())
        {
            return std::unexpected(ParseError{
                MissingPackageSection,
                "Missing [package] section in forge.toml."
            });
        }
        Core::Package package;

        const auto& package_table = data["package"];
        if (const auto name = package_table["name"].value<std::string>())
        {
            package.name = std::move(name.value());
        }
        else
        {
            return std::unexpected(ParseError{
                MissingPackageSection,
                "Missing required 'name' field in [package] section"
            });
        }

        if (const auto version = package_table["version"].value<std::string_view>())
        {
            if (auto result = parse_version(version.value()))
            {
                package.version = result.value();
            }
            else
            {
                return std::unexpected(result.error());
            }
        }
        else
        {
            return std::unexpected(ParseError{
                MissingPackageSection,
                "Missing required 'version' field in [package] section"
            });
        }
        package.description = std::move(package_table["description"].value_or(""s));
        package.license = std::move(package_table["license"].value_or(""s));
        package.repository = std::move(package_table["repository"].value_or(""s));
        if (const auto authors = package_table["authors"].as_array())
        {
            for (auto&& author : *authors)
            {
                if (auto author_str = author.value<std::string>())
                {
                    package.authors.push_back(*author_str);
                }
            }
        }


        if (const auto targets_array = data["targets"].as_array())
        {
            for (auto&& target_element : *targets_array)
            {
            }
        }

        return std::move(package);
    };

    std::expected<Core::Target, ParseError> parse_target(const node_view<const node>& target_element)
    {
        if (const auto target_table = target_element.as_table())
        {
            Core::Target target;
            target.name = (*target_table)["name"].value_or(""s);
            target.src_dir = (*target_table)["src_dir"].value_or(""s);
            target.include_dir = (*target_table)["include_dir"].value_or(""s);
            target.target_type = (*target_table)["type"].value_or(""s);
            return std::move(target);
        }
        return std::unexpected(ParseError{
            InvalidTargetDefinition, "Unexpected exception occurred."
        });
    };

    std::expected<Core::Dependency, ParseError> parse_dependency(node_view<const node>& node_view)
    {
    };

    std::expected<Core::Version, ParseError> parse_version(std::string_view versionStr)
    {
        auto parse_uint = [](const std::string_view sv) -> std::expected<unsigned int, ParseError>
        {
            unsigned int value;
            auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
            if (ec != std::errc{} || ptr != sv.data() + sv.size())
            {
                return std::unexpected(ParseError{InvalidPackageVersion, "Invalid number in version string"});
            }
            return value;
        };

        std::vector<unsigned int> parts;
        for (auto part_range : versionStr | std::ranges::views::split('.'))
        {
            const std::string_view part_sv(part_range.begin(), part_range.end());
            auto result = parse_uint(part_sv);
            if (!result)
            {
                return std::unexpected(result.error());
            }
            parts.push_back(result.value());
        }
        if (parts.size() != 3)
        {
            return std::unexpected(ParseError{
                InvalidPackageVersion,
                "Version must have exactly 3 parts (major.minor.patch)"
            });
        }

        return Core::Version{parts[0], parts[1], parts[2]};
    };
}
