#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/shared-utils.sh"

# Build project
make build

# Generate compile_commands.json
make compile_commands

# Run devcontainer tests
echo ""
if bash "$SCRIPT_DIR/test-workspace.sh"; then
    echo ""
    echo "🎉 DevContainer setup is complete!"
    echo ""
else
    echo ""
    echo "❌ DevContainer setup failed!"
    echo ""
    exit 1
fi
