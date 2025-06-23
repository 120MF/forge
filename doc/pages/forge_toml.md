# Forge's TOML Config file

Here's an introduction of how Forge's TOML file (forge.toml) manages Forge package.

## Package Information

```toml
[package]
name = "package-name"
version = "0.1.0"
description = ""
authors = ["author <email@example.com>"]
license = "MIT"
repository = "https://github.com/username/project"
```

## Package Target

## Package Dependencies

```toml
[dependencies]
fmt = "8.0.1"
eigen = { version = "3.4.0", features = ["sparse"] }
boost = { version = "1.79.0", optional = true }
```

## Build Configuration

```toml
[build]
cmake_minimum = "3.15"
cpp_standard = "17"
include_dirs = ["include"]
src_dirs = ["src"]
test_dirs = ["tests"]
```

## Target Platform

```toml
[platform]
os = ["linux", "windows", "macos"]
arch = ["x86_64", "arm64"]
```

## Features

```toml
[features]
default = ["logging"]
logging = []
network = ["dependencies.boost"]
```

## Package Publish

```toml
[package.publish]
exclude = ["*.log", "build/", "tests/"]
include = ["LICENSE", "README.md"]
```