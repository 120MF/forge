# CMake Project Integration

There are many projects that only uses CMake to generate targets and do not want to introduce other layers of complexity (for
example, `forge.toml`). Therefore, `Forge` supports series of `CMake Command` to **import package from forge** or **export target to forge**.

## Import Forge Package

```cmake
find_package(forge REQUIRED)
forge_import_dependency(fmt)
```

## Export CMake Target

```cmake
find_package(forge)
if(FORGE_FOUND)
    forge_export_package(
            NAME ${PROJECT_NAME}
            VERSION ${PROJECT_VERSION}
            DESCRIPTION "a normal CMake lib"
            TARGETS mylib
    )
endif ()
```