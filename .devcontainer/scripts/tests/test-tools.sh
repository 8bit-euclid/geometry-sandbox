#!/bin/bash
# C++23 and Bazel tools verification test script
set -euo pipefail

# Source utilities and initialize paths
source "$(dirname "${BASH_SOURCE[0]}")/../shared-utils.sh"
init_test_paths

test_tool() {
    local tool_name="$1"
    local test_command="$2"

    if eval "$test_command" &>/dev/null; then
        log_success "$tool_name is working"
    else
        log_error "$tool_name failed"
    fi
}

test_cpp_compiler() {
    local compiler="$1"
    local version_flag="$2"

    if command_exists "$compiler"; then
        local version_output
        version_output=$($compiler $version_flag 2>&1)

        # Check for C++23 support
        if echo "$version_output" | grep -qE "(gcc|g\+\+).*(1[3-9]|[2-9][0-9])" ||
           echo "$version_output" | grep -qE "clang.*(1[5-9]|[2-9][0-9])"; then
            log_success "$compiler supports C++23"
        else
            log_warning "$compiler may have limited C++23 support"
        fi
    else
        log_error "$compiler not found"
    fi
}

test_development_tools() {
    # Test C++ compilers
    test_cpp_compiler "g++" "--version"
    test_cpp_compiler "clang++" "--version"

    # Test essential build tools
    test_tool "Make" "make --version"
    test_tool "GDB" "gdb --version"

    # Test Bazel
    if command_exists bazel; then
        test_tool "Bazel" "bazel version"

        # Test Bazel workspace/module
        cd "$WORKSPACE_ROOT"
        if [ -f "WORKSPACE" ] || [ -f "WORKSPACE.bazel" ] || [ -f "MODULE.bazel" ]; then
            if bazel query //... &>/dev/null; then
                log_success "Bazel workspace/module is valid"
            else
                log_warning "Bazel workspace/module may have issues"
            fi
        else
            log_warning "No Bazel workspace or module found"
        fi
    else
        log_error "Bazel not found"
    fi

    # Test Buildifier
    if command_exists buildifier; then
        test_tool "Buildifier" "buildifier --version"
    else
        log_error "Buildifier not found"
    fi
}

# Main function - standardized entry point
main() {
    test_development_tools
}

# Run tests if script is executed directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    print_heading "🔧 C++23 & Bazel Tools Test"
    main
    exit $EXIT_CODE
fi
