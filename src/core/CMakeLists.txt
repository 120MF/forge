add_library(ForgeCore)
file(GLOB_RECURSE FORGE_CORE_SOURCES "*.cpp")
target_sources(ForgeCore PRIVATE ${FORGE_CORE_SOURCES})
target_include_directories(ForgeCore PUBLIC ${PROJECT_SOURCE_DIR}/include/forge/core)