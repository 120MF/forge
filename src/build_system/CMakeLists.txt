add_library(ForgeBuildSystem)

file(GLOB_RECURSE FORGE_BUILDSYSTEM_SOURCES "*.cpp")
target_sources(ForgeBuildSystem PRIVATE ${FORGE_BUILDSYSTEM_SOURCES})
target_include_directories(ForgeBuildSystem PUBLIC ${PROJECT_SOURCE_DIR}/include/forge/build_system)

target_link_libraries(ForgeBuildSystem PRIVATE ForgeCore)