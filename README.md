# Petri

C++ sandbox for experiments.

## Usage

| Depenency      | Version |
|----------------|---------|
| just           | Latest  |
| uv             | Latest  |
| CMake          | Latest  |
| Conan          | Latest  |
| MSVC/GCC/Clang | Latest  |

```sh
# Pass MULTI_CONFIG=true for multi-config generators
just all config="debug"       # Configure + build
just configure config="debug" # Configure
just build config="debug"     # Build
just new name                 # New project
```
