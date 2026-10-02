# Petri

C++ sandbox for experiments.

## Layout

- `src/` – experiments, one folder each
- `tools/` – helper scripts

## Usage

```sh
uv venv

# For Windows
.venv\Scripts\activate
# For Linux
source .venv/bin/activate

uv pip install -U -r ./requirements.txt
conan profile detect

# For Windows
conan install . --build=missing -s build_type=Debug -s compiler.runtime_type=Debug
# For Linux
conan install . --build=missing -s build_type=Debug

python tools/new.py <new_experiment_name>

cmake --preset <preset>
cmake --build ./build/<config> --parallel
```
