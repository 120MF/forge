include(FetchContent)
FetchContent_Declare(
        cli11_proj
        QUIET
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(cli11_proj)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.2.0
)
FetchContent_MakeAvailable(fmt)

add_executable(forge)
file(GLOB_RECURSE FORGE_CLI_SOURCES "*.cpp")
target_sources(forge PRIVATE ${FORGE_CLI_SOURCES})
target_include_directories(forge PRIVATE ${PROJECT_SOURCE_DIR}/include/forge/cli)
target_link_libraries(forge PRIVATE CLI11::CLI11 fmt::fmt ForgeCore ForgeBuildSystem)
