# Forge's TOML Config file

Here's an introduction of how Forge's TOML file (forge.toml) manages Forge package.

```toml
# forge.toml

[package]
name = "MyAwesomeProject"
description = "A description of my awesome project."
version = "0.1.0"
authors = ["120MF <user@example.com>"]
license = "MIT"
repository = "https://github.com/120MF/MyAwesomeProject"

[[targets]]
src_dir = "src/lib"
include_dir = "include/lib"

[[targets]]
src_dir = "src/app"
include_dir = "include/app"
```