#!/bin/bash

set -euo pipefail

# Get script directory and source utilities
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/shared-utils.sh"

echo "🚀 Setting up C++23 Bazel development environment..."

# Ensure we're in the workspace directory
cd /workspace

# Fix workspace permissions to ensure files can be saved
echo "🔧 Fixing workspace permissions..."
if sudo chown -R vscode:vscode /workspace 2>/dev/null && sudo chmod -R u+w /workspace 2>/dev/null; then
    log_success "Workspace permissions fixed"
else
    log_warning "Could not fix workspace permissions, continuing..."
fi

# Verify C++23 compiler support
echo "🔧 Verifying C++23 compiler support..."
if g++ --version | grep -q "13\|14\|15"; then
    log_success "C++23 compatible compiler available"
else
    log_warning "C++23 support may be limited with current compiler"
fi

# Ensure clang++ symlink exists for test compatibility
echo "🔗 Setting up clang++ symlink..."
if [ -f "/usr/bin/clang++-18" ] && [ ! -f "/usr/bin/clang++" ]; then
    if sudo ln -sf /usr/bin/clang++-18 /usr/bin/clang++; then
        log_success "clang++ symlink created"
    else
        log_warning "Could not create clang++ symlink"
    fi
elif [ -f "/usr/bin/clang++" ]; then
    log_success "clang++ already available"
else
    log_warning "clang++ not found"
fi

# Initialize Bazel module if MODULE.bazel doesn't exist
if [ ! -f "WORKSPACE" ] && [ ! -f "WORKSPACE.bazel" ] && [ ! -f "MODULE.bazel" ]; then
    echo "📦 Initializing Bazel module..."
    cat > MODULE.bazel << 'EOF'
module(
    name = "geometry_sandbox",
    version = "1.0.0",
)

# C++ rules
bazel_dep(name = "rules_cc", version = "0.0.9")

# Optional: Google Test for testing
bazel_dep(name = "googletest", version = "1.14.0")
EOF
    log_success "Bazel module initialized"
fi

# Create a basic .bazelrc if it doesn't exist
if [ ! -f ".bazelrc" ]; then
    echo "🔧 Creating .bazelrc with C++23 and MODULE settings..."
    cat > .bazelrc << 'EOF'
# Enable Bzlmod (MODULE.bazel system)
common --enable_bzlmod

# C++23 configuration
build --cxxopt=-std=c++23
build --host_cxxopt=-std=c++23

# Optimization flags
build --copt=-O2
build --copt=-DNDEBUG

# Debug configuration
build:debug --copt=-g
build:debug --copt=-O0
build:debug --strip=never

# Compiler-specific flags
build --cxxopt=-Wall
build --cxxopt=-Wextra
build --cxxopt=-Wpedantic

# Modern C++ features
build --cxxopt=-fcoroutines
build --cxxopt=-fmodules-ts
EOF
    log_success ".bazelrc created with C++23 and MODULE settings"
fi
