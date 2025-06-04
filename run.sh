#!/bin/bash
set -e

# Fail if no source file is provided
SOURCE="/home/runner/source_code.ffo"
if [ ! -f "$SOURCE" ]; then
	echo "Error: source_code.ffo not found." >&2
	exit 1
fi

# Run the compiler on the input file with a timeout
timeout 5s sacompiler "$SOURCE"
