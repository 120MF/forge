include(FetchContent)
FetchContent_Declare(
        tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

add_library(ForgeCore)
file(GLOB_RECURSE FORGE_CORE_SOURCES "*.cpp")
target_sources(ForgeCore PRIVATE ${FORGE_CORE_SOURCES})
target_include_directories(ForgeCore PUBLIC ${PROJECT_SOURCE_DIR}/include/forge/core)
target_link_libraries(ForgeCore PRIVATE tomlplusplus::tomlplusplus)