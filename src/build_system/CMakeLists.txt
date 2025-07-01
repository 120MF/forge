include(FetchContent)
FetchContent_Declare(
        tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

add_library(ForgeBuildSystem)

file(GLOB_RECURSE FORGE_BUILDSYSTEM_SOURCES "*.cpp")
target_sources(ForgeBuildSystem PRIVATE ${FORGE_BUILDSYSTEM_SOURCES})
target_include_directories(ForgeBuildSystem PUBLIC ${PROJECT_SOURCE_DIR}/include/forge/build_system)

target_compile_definitions(ForgeBuildSystem PUBLIC
        TOML_EXCEPTIONS=0
        TOML_HEADER_ONLY=0
        TOML_IMPLEMENTATION
        
)
target_link_libraries(ForgeBuildSystem PRIVATE ForgeCore tomlplusplus::tomlplusplus)