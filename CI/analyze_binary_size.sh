#!/usr/bin/env bash
set -eu
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ANALYZER_PYTHON=python3
for candidate in "$SCRIPT_DIR/../.venv/bin/python" "$SCRIPT_DIR/../.venv/python/python" "$SCRIPT_DIR/../.venv/python/python.exe"; do
    if [[ -x "$candidate" ]]; then
        ANALYZER_PYTHON="$candidate"
        break
    fi
done
exec "$ANALYZER_PYTHON" "$SCRIPT_DIR/scripts/analyze_binary_size.py" "$@"
