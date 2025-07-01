#ifndef FORGE_VERSION_HPP
#define FORGE_VERSION_HPP

#include <string>

namespace Forge::Core
{
    struct Version
    {
        unsigned int major{};
        unsigned int minor{};
        unsigned int patch{};
        Version() = default;

        Version(const unsigned int major, const unsigned int minor, const unsigned patch): major(major),
            minor(minor), patch(patch)
        {
        }

        [[nodiscard]] auto to_tuple() const noexcept;
        [[nodiscard]] std::string to_string() const noexcept;

        auto operator<=>(const Version&) const = default;
    };
}

#endif //FORGE_VERSION_HPP
