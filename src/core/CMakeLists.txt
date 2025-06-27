include(FetchContent)
FetchContent_Declare(
        toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG v4.4.0
)
FetchContent_MakeAvailable(toml11)

add_library(ForgeCore)
file(GLOB_RECURSE FORGE_CORE_SOURCES "*.cpp")
target_sources(ForgeCore PRIVATE ${FORGE_CORE_SOURCES})
target_include_directories(ForgeCore PUBLIC ${PROJECT_SOURCE_DIR}/include/forge/core)
target_link_libraries(ForgeCore PRIVATE toml11::toml11)