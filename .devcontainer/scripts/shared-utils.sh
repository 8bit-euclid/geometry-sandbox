#!/bin/bash

# Shared utilities for devcontainer test scripts
# This file should be sourced by other test scripts

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;38;5;178m'
RED='\033[1;31m'
NC='\033[0m'

# Exit code tracking
EXIT_CODE=0

# Initialize common paths for test scripts
init_test_paths() {
    # Set SCRIPT_DIR to the directory of the calling script
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[1]}")" && pwd)"
    # Set WORKSPACE_ROOT to the repository root (3 levels up from test scripts)
    WORKSPACE_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"
}

# Logging functions
log_success() { echo -e "${GREEN}✓ $1${NC}"; }
log_warning() { echo -e "${YELLOW}⚠ $1${NC}"; }
log_error() { echo -e "${RED}✗ $1${NC}"; EXIT_CODE=1; }

# Environment detection
is_devcontainer() {
    [[ "${DEVCONTAINER:-}" == "1" ]]
}

# Check if we're in a post-creation environment (just after devcontainer setup)
is_post_creation() {
    # Check if this is being run as part of postCreateCommand
    [[ "${DEVCONTAINER:-}" == "1" ]] && [[ -n "${VSCODE_INJECTION:-}" ]]
}

# Build utilities
test_cpp23_support() {
    local compiler="$1"
    if command_exists "$compiler"; then
        # Create a simple C++23 test
        local test_file="/tmp/cpp23_test_$$.cpp"
        echo '#include <version>' > "$test_file"
        echo 'int main() { return 0; }' >> "$test_file"

        if "$compiler" -std=c++23 -c "$test_file" -o /tmp/cpp23_test_$$.o 2>/dev/null; then
            rm -f "$test_file" /tmp/cpp23_test_$$.o
            return 0
        else
            rm -f "$test_file"
            return 1
        fi
    else
        return 1
    fi
}

# Print heading
print_heading() {
    print_blank_line
    print_section "$1"
    print_hline
}

# Print a horizontal line
print_hline() {
    echo "================================"
}

# Print an underline
print_underline() {
    echo "----------------------"
}

# Test section header
print_section() {
    echo -e "$1"
}

# Print a blank line
print_blank_line() {
    echo ""
}

# Check if command exists
command_exists() {
    command -v "$1" &>/dev/null
}

# Validate JSON file
validate_json() {
    local file="$1"
    if [[ -f "$file" ]]; then
        if python3 -c "import json; json.load(open('$file'))" 2>/dev/null; then
            return 0
        else
            return 1
        fi
    else
        return 1
    fi
}

# Get available disk space
get_disk_space() {
    local path="$1"
    df -h "$path" | awk 'NR==2 {print $4}'
}

# Check if port is in use
is_port_in_use() {
    local port="$1"
    lsof -Pi ":$port" -sTCP:LISTEN -t &>/dev/null
}

# Extract repository name from GitHub environment or git remote
get_repo_name() {
    [[ -n "${GITHUB_REPOSITORY:-}" ]] && echo "$GITHUB_REPOSITORY" && return

    local workspace_root="${WORKSPACE_ROOT:-$(pwd)}"
    local remote_url=$(git -C "$workspace_root" remote get-url origin 2>/dev/null || echo "")
    if [[ "$remote_url" =~ git@github\.com[^:]*:([^/]+/[^/]+)\.git$ ]] ||
       [[ "$remote_url" =~ git@github\.com[^:]*:([^/]+/[^/]+)$ ]] ||
       [[ "$remote_url" =~ https://github\.com/([^/]+/[^/]+)\.git$ ]] ||
       [[ "$remote_url" =~ https://github\.com/([^/]+/[^/]+)$ ]]; then
        echo "${BASH_REMATCH[1]}"
    fi
}
