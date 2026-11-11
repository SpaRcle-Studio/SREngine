#!/usr/bin/env bash

if [ "$#" -eq 0 ]; then
    echo "Usage: bash CI/retry.sh command [args...]" >&2
    exit 2
fi

delay=15
for attempt in 1 2 3 4; do
    if "$@"; then
        exit 0
    else
        status=$?
    fi

    if [ "$status" -eq 130 ] || [ "$status" -eq 143 ]; then
        exit "$status"
    fi

    if [ "$attempt" -eq 4 ]; then
        echo "::error::Command failed after $attempt attempts (exit $status)."
        exit "$status"
    fi

    echo "::warning::Attempt $attempt failed (exit $status); retrying in ${delay}s."
    sleep "$delay"
    delay=$((delay * 2))
done
