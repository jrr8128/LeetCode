#!/usr/bin/env bash
set -euo pipefail

[[ $# -ge 1 ]] || { echo "usage: ./build.sh path/to/solution.cpp"; exit 1; }

SRC="$(realpath "$1")"
DIR="$(dirname "$SRC")"
BASE="$(basename "$SRC" .cpp)"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CATCH_INC="$ROOT/third_party/catch2"
CATCH_CPP="$CATCH_INC/catch_amalgamated.cpp"
BUILD_DIR="$ROOT/build"
CATCH_OBJ="$BUILD_DIR/catch_amalgamated.o"

mkdir -p "$BUILD_DIR"

# rebuild Catch2 object if missing or stale
if [[ ! -f "$CATCH_OBJ" || "$CATCH_CPP" -nt "$CATCH_OBJ" ]]; then
  clang++ -std=c++23 -O0 -g -Wall -Wextra -I "$CATCH_INC" -c "$CATCH_CPP" -o "$CATCH_OBJ"
fi

clang++ -std=c++23 -O0 -g -Wall -Wextra -I "$CATCH_INC" \
  "$SRC" "$CATCH_OBJ" -o "$DIR/$BASE"
