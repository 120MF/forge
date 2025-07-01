#ifndef FORGE_VERSION_HPP
#define FORGE_VERSION_HPP

#include <cstdint>
#include <string>

namespace Forge::Core
{
    struct Version
    {
        uint8_t major{};
        uint8_t minor{};
        uint8_t patch{};
        Version() = default;
        explicit Version(const std::string& versionStr);
        [[nodiscard]] auto to_tuple() const noexcept;
        [[nodiscard]] auto to_string() const noexcept;

        auto operator<=>(const Version&) const = default;
    };
}

#endif //FORGE_VERSION_HPP
