#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RAYLIB_SRC="$ROOT_DIR/build/external/raylib-master/src"
OUTPUT_DIR="$ROOT_DIR/bin/Web"

command -v emcc >/dev/null 2>&1 || {
    echo "Error: emcc is not available."
    exit 1
}

mkdir -p "$OUTPUT_DIR"

(
    cd "$RAYLIB_SRC"

    emmake make clean || true

    emmake make \
        PLATFORM=PLATFORM_WEB \
        RAYLIB_LIBTYPE=STATIC \
        -j"$(nproc)"
)

RAYLIB_LIBRARY="$(
    find "$RAYLIB_SRC" \
        -maxdepth 2 \
        -type f \
        -name 'libraylib*.a' \
        | head -n 1
)"

if [[ -z "$RAYLIB_LIBRARY" ]]; then
    echo "Error: raylib WebAssembly library was not produced."
    exit 1
fi

mapfile -t SOURCES < <(
    find "$ROOT_DIR/src" \
        -maxdepth 1 \
        -type f \
        -name '*.c'
)

emcc \
    "${SOURCES[@]}" \
    "$RAYLIB_LIBRARY" \
    -I"$ROOT_DIR/include" \
    -I"$RAYLIB_SRC" \
    -std=c11 \
    -O2 \
    -DPLATFORM_WEB \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    -s ALLOW_MEMORY_GROWTH=1 \
    --preload-file "$ROOT_DIR/resources@resources" \
    --shell-file "$ROOT_DIR/web/shell.html" \
    -o "$OUTPUT_DIR/index.html"