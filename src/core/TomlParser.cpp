#include "TomlParser.hpp"
#include "toml.hpp"
namespace Forge
{
    Package parse_forge_toml(const std::filesystem::path& toml_path)
    {
        if (!std::filesystem::exists(toml_path)) {
            throw std::runtime_error("forge.toml not found at: " + toml_path.string());
        }

        // 1. 解析 TOML 文件
        const auto data = toml::parse(toml_path);
        Forge::Package package;

        // 2. 解析 [package] 表
        const auto& package_table = toml::find(data, "package");

        package.name = toml::find<std::string>(package_table, "name");
        package.description = toml::find<std::string>(package_table, "description");

        // 使用 Version 的构造函数
        package.version = Forge::Version(toml::find<std::string>(package_table, "version"));

        // toml11 会将 TOML 数组解析为 std::vector
        const auto authors_vec = toml::find<std::vector<std::string>>(package_table, "authors");
        package.authors.insert(authors_vec.begin(), authors_vec.end());

        package.license = toml::find<std::string>(package_table, "license");
        package.repository = toml::find<std::string>(package_table, "repository");

        // 3. 解析 [[targets]] 表数组
        if (data.contains("targets")) {
            for (const auto& targets_array = toml::find<toml::array>(data, "targets"); const auto& target_table : targets_array) {
                Target target;
                target.src_dir = toml::find<std::string>(target_table, "src_dir");
                target.include_dir = toml::find<std::string>(target_table, "include_dir");
                package.targets.insert(target);
            }
        }

        return package;
    }

}