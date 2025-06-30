#ifndef CACHEMANAGER_HPP
#define CACHEMANAGER_HPP

#include <filesystem>
#include "Package.hpp"

namespace Forge
{
    class CacheManager
    {
    public:
        CacheManager();
        std::filesystem::path getBuildPath();
    };
}

#endif //CACHEMANAGER_HPP
