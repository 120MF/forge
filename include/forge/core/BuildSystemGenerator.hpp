#ifndef BUILDSYSTEMGENERATOR_HPP
#define BUILDSYSTEMGENERATOR_HPP

#include <filesystem>

namespace Forge
{
    class BuildSystemGenerator
    {
    public:
        void generate(const class ForgePackage& package, const std::filesystem::path& outputDir);

    };
}

#endif //BUILDSYSTEMGENERATOR_HPP
