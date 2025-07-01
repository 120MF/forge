#include "TomlParser.hpp"
#include <toml++/toml.hpp>
using std::literals::operator ""s;

namespace Forge::BuildSystem
{
    Core::Package parse_forge_toml(const std::filesystem::path& toml_path)
    {
        if (!std::filesystem::exists(toml_path)) {
            throw std::runtime_error("forge.toml not found at: " + toml_path.string());
        }

        const auto data = toml::parse_file(toml_path.generic_u8string());
        Core::Package package;

        const auto package_table = data["package"];

        package.name = package_table["name"].value_or(""s);
        package.description = package_table["description"].value_or(""s);
        package.version = Core::Version(package_table["version"].value_or(""s));

        if (const auto authors = package_table["authors"].as_array()) {
            for (auto&& author : *authors) {
                if (auto author_str = author.value<std::string>()) {
                    package.authors.push_back(*author_str);
                }
            }
        }

        package.license = package_table["license"].value_or(""s);
        package.repository = package_table["repository"].value_or(""s);

        if (const auto targets_array = data["targets"].as_array()) {
            for (auto&& target_element : *targets_array) {
                if (const auto target_table = target_element.as_table()) {
                    Core::Target target;
                    target.name = (*target_table)["name"].value_or(""s);
                    target.src_dir = (*target_table)["src_dir"].value_or(""s);
                    target.include_dir = (*target_table)["include_dir"].value_or(""s);
                    target.target_type = (*target_table)["type"].value_or(""s);
                    package.targets.push_back(target);
                }
            }
        }

        return package;
    }
}