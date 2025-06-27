cmake_minimum_required(VERSION 3.20)
project(forge VERSION 0.1.0)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

include(ForgeDocument)
include(ForgeInstall)