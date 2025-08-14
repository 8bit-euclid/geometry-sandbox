#!/bin/bash
# C++23 Bazel build test script
set -euo pipefail

# Source utilities and initialize paths
source "$(dirname "${BASH_SOURCE[0]}")/../shared-utils.sh"
init_test_paths

test_cpp_compilation() {
    print_section "Testing C++23 compilation..."

    # Create a temporary C++23 test file
    local test_file="/tmp/cpp23_test.cpp"
    cat > "$test_file" << 'EOF'
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // C++23 features test
    auto even_numbers = numbers
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * 2; });

    for (auto n : even_numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
EOF

    # Test compilation with g++
    if g++ -std=c++23 -o /tmp/cpp23_test_gcc "$test_file" 2>/dev/null; then
        log_success "C++23 compilation with g++ works"

        # Test execution
        if /tmp/cpp23_test_gcc &>/dev/null; then
            log_success "C++23 executable (g++) runs successfully"
        else
            log_warning "C++23 executable (g++) failed to run"
        fi

        rm -f /tmp/cpp23_test_gcc
    else
        log_error "C++23 compilation with g++ failed"
    fi

    # Test compilation with clang++
    if clang++-18 -std=c++23 -stdlib=libc++ -o /tmp/cpp23_test_clang "$test_file" 2>/dev/null; then
        log_success "C++23 compilation with clang++ works"

        # Test execution
        if /tmp/cpp23_test_clang &>/dev/null; then
            log_success "C++23 executable (clang++) runs successfully"
        else
            log_warning "C++23 executable (clang++) failed to run"
        fi

        rm -f /tmp/cpp23_test_clang
    else
        log_error "C++23 compilation with clang++ failed"
    fi

    # Clean up test file
    rm -f "$test_file"
}

test_bazel_build() {
    print_section "Testing Bazel build system..."

    cd "$WORKSPACE_ROOT"

    # Check if Bazel workspace exists
    if [ -f "MODULE.bazel" ]; then
        log_success "Bazel workspace found"

        # Test basic Bazel query
        if bazel query //... &>/dev/null; then
            log_success "Bazel query works"
        else
            log_error "Bazel query failed"
        fi
    else
        log_warning "No Bazel workspace found - skipping Bazel tests"
    fi
}

# Main function - standardized entry point
main() {
    test_cpp_compilation
    test_bazel_build
}

# Run test if script is executed directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    print_heading "🏗️ C++23 & Bazel Build Test"
    main
    exit $EXIT_CODE
fi
