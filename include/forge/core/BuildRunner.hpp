#ifndef BUILDRUNNER_HPP
#define BUILDRUNNER_HPP

#include <filesystem>

namespace Forge
{
    class BuildRunner
    {
    public:
        bool run(const std::filesystem::path& buildPath);

    private:
        bool configure(const std::filesystem::path& buildPath);
        bool build(const std::filesystem::path& buildPath);
    };
}

#endif //BUILDRUNNER_HPP
