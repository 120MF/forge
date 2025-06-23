cmake_minimum_required(VERSION 3.20)
project(forge VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
            COMMENT "Generate doxygen document"
            VERBATIM
    )
endif ()

add_subdirectory(src)