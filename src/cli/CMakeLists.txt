include(FetchContent)
FetchContent_Declare(
        cli11_proj
        QUIET
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.3.2
)

FetchContent_MakeAvailable(cli11_proj)

add_executable(forge
        main.cpp
)
target_link_libraries(forge PRIVATE CLI11::CLI11)
