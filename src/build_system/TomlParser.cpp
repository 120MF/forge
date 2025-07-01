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
    std::expected<Core::Target, ParseError> parse_target(const node& target_element);
    std::expected<Core::Dependency, ParseError> parse_dependency(const node& dependency_node);

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
        if (auto name = package_table["name"].value<std::string>())
            package.name = std::move(name.value());
        else
            return std::unexpected(ParseError{
                MissingPackageSection,
                "Missing required 'name' field in [package] section"
            });

        if (const auto version = package_table["version"].value<std::string_view>())
        {
            if (auto result = parse_version(version.value()))
                package.version = result.value();
            else
                return std::unexpected(result.error());
        }
        else
            return std::unexpected(ParseError{
                MissingPackageSection,
                "Missing required 'version' field in [package] section"
            });
        package.description = std::move(package_table["description"].value<std::string>());
        package.license = std::move(package_table["license"].value<std::string>());
        package.repository = std::move(package_table["repository"].value<std::string>());
        if (const auto authors = package_table["authors"].as_array())
        {
            std::vector<std::string> authors_vec;
            authors_vec.reserve(authors->size());
            for (const auto& author : *authors)
            {
                if (auto author_str = author.value<std::string>())
                {
                    authors_vec.push_back(std::move(author_str.value()));
                }
            }

            if (!authors_vec.empty())
            {
                package.authors = std::move(authors_vec);
            }
        }


        if (const auto targets_array = data["targets"].as_array())
        {
            for (auto&& target_node : *targets_array)
            {
                auto target = parse_target(target_node);
                if (!target) return std::unexpected(target.error());
                package.targets.push_back(std::move(target.value()));
            }
        }

        return std::move(package);
    };

    std::expected<Core::Target, ParseError> parse_target(const node& target_element)
    {
        if (const auto target_table = target_element.as_table())
        {
            Core::Target target;
            if (auto name = (*target_table)["name"].value<std::string>())
                target.name = std::move(name.value());
            else
                return std::unexpected(ParseError{
                    InvalidTargetDefinition, "Missing required 'name' field in [[target]] section"
                });
            target.src_dir = (*target_table)["src_dir"].value_or(""s);
            target.include_dir = (*target_table)["include_dir"].value_or(""s);
            target.target_type = (*target_table)["type"].value_or(""s);

            if (const auto dependencies = (*target_table)["dependencies"].as_array())
            {
                for (auto&& dependency_node : *dependencies)
                {
                    auto dependency = parse_dependency(dependency_node);
                    if (dependency)
                    {
                        target.dependencies.push_back(std::move(dependency.value()));
                        continue;
                    }
                    return std::unexpected(dependency.error());
                }
            }
            return std::move(target);
        }
        return std::unexpected(ParseError{
            InvalidTargetDefinition, "Unexpected exception occurred."
        });
    };

    std::expected<Core::Dependency, ParseError> parse_dependency(const node& dependency_node)
    {
        Core::Dependency dependency;
        if (auto dep_str = dependency_node.value<std::string>())
        {
            dependency.name = std::move(dep_str.value());
            return std::move(dependency);
        }

        if (const auto dep_table = dependency_node.as_table())
        {
            if (auto name = (*dep_table)["name"].value<std::string>())
                dependency.name = std::move(name.value());
            else
                return std::unexpected(ParseError{
                    InvalidDependencyDefinition,
                    "Missing required 'name' field in dependency definition"
                });
            if (const auto version = (*dep_table)["version"].value<std::string>())
            {
                if (const auto result = parse_version(version.value()))
                    dependency.version = result.value();
                else
                    return std::unexpected(result.error());
            }
            dependency.git = std::move((*dep_table)["git"].value<std::string>());
            dependency.tag = std::move((*dep_table)["tag"].value<std::string>());
            dependency.type = std::move((*dep_table)["type"].value<std::string>());
            if (const auto targets_array = (*dep_table)["targets"].as_array())
            {
                std::vector<std::string> targets;
                for (auto&& target_node : *targets_array)
                {
                    if (auto target_str = target_node.value<std::string>())
                        targets.push_back(std::move(target_str.value()));
                }
                dependency.target_names = std::move(targets);
            }
            return std::move(dependency);
        }
        return std::unexpected(ParseError{
            InvalidDependencyDefinition,
            "Dependency must be either a string or a table"
        });
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
