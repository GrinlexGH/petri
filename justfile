set default-list
multi_config := env("MULTI_CONFIG", "false")

# Configure + build
all config="debug": (configure config) (build config)

# Configure
configure config="debug":
    uv venv --allow-existing
    uv pip install -r requirements.txt
    uv run conan profile detect --exist-ok
    uv run conan remote add petri ./conan/conan-recipes/ -t local-recipes-index --force
    uv run conan install . -r petri --build=missing -s build_type={{ capitalize(config) }}{{ if os_family() == "windows" { " -s compiler.runtime_type=" + capitalize(config) } else { "" } }}
    uv run cmake --preset {{ if multi_config == "true" { "conan-default" } else { "conan-" + config } }}

# Build
build config="debug":
    uv run cmake --build --preset conan-{{ config }} --parallel

# New project
new name:
    uv run python tools/new.py {{ name }}

[windows]
set shell := ["pwsh.exe", "-NoLogo", "-NoProfile", "-Command"]
