# C++23 Bazel Development Container

This devcontainer is configured for modern C++23 development using Bazel as the build system.

## Features

- **C++23 Support**: GCC 13+ and Clang 18+ with full C++23 standard support
- **Bazel Build System**: Latest Bazelisk for managing Bazel versions
- **Development Tools**: GDB, Valgrind, and Buildifier for code formatting
- **VS Code Integration**: C++ IntelliSense and Bazel extension support

## Getting Started

1. **Open in DevContainer**: Use VS Code's "Reopen in Container" command
2. **Wait for Setup**: The container will automatically set up the C++23 environment
3. **Automatic Validation**: Post-creation tests run automatically to verify the setup
4. **Manual Testing**: You can also run tests manually anytime:
   ```bash
   bash .devcontainer/scripts/test-workspace.sh
   ```

## C++23 Configuration

The devcontainer includes:
- **GCC 13**: Set as default compiler with C++23 support
- **Clang 18**: Alternative compiler with C++23 support
- **Bazel MODULE System**: Modern Bzlmod with MODULE.bazel instead of legacy WORKSPACE
- **Bazel Configuration**: Pre-configured .bazelrc with C++23 and Bzlmod settings

## Testing

### Run All Tests
```bash
bash .devcontainer/scripts/test-workspace.sh
```

### Run Individual Test Categories
```bash
# Configuration validation
bash .devcontainer/scripts/tests/test-config.sh

# C++23 and Bazel tools
bash .devcontainer/scripts/tests/test-tools.sh

# System resource checks
bash .devcontainer/scripts/tests/test-resources.sh

# C++23 compilation and Bazel build testing
bash .devcontainer/scripts/tests/test-build.sh
```

The streamlined test system includes:
- **Configuration validation**: JSON syntax, file existence
- **Tool verification**: C++23 compilers, Bazel, Buildifier availability
- **System resources**: Disk space and memory usage
- **Build testing**: C++23 compilation and Bazel build system verification

## Troubleshooting

### C++23 Compilation Issues
If C++23 features don't compile:
- Verify you're using GCC 13+ or Clang 18+ with `g++ --version` or `clang++ --version`
- Check that `-std=c++23` flag is being used
- Some C++23 features may require additional compiler flags

### Bazel Build Issues
If Bazel builds fail:
- Ensure MODULE.bazel file exists in project root (modern Bzlmod system)
- Check .bazelrc configuration for C++23 and Bzlmod settings
- Run `bazel clean` to clear build cache if needed
- Verify BUILD files have correct syntax with `buildifier`

### Post-Creation Test Failures
If tests fail during devcontainer creation:
- The devcontainer will still be created successfully
- Run `bash .devcontainer/scripts/test-workspace.sh` manually after setup completes
- Check individual test categories to isolate issues

### Permission Issues
If you encounter file permission errors:
- Ensure you're using the `vscode` user (default)
- The setup script automatically fixes workspace permissions
- Restart the devcontainer if issues persist

## Configuration Files

- **devcontainer.json**: Main devcontainer configuration for C++23 development
- **Dockerfile**: Ubuntu 24.04 base with GCC 13, Clang 18, and Bazel
- **scripts/shared-utils.sh**: Shared utilities and logging functions for all scripts
- **scripts/post-create.sh**: Post-creation validation script (runs automatically)
- **scripts/setup-workspace.sh**: Workspace initialization with Bazel configuration

### Test Scripts

- **scripts/test-workspace.sh**: Main test orchestrator that runs all test categories
- **scripts/tests/test-config.sh**: Configuration file validation (JSON syntax, file existence)
- **scripts/tests/test-tools.sh**: C++23 compiler and Bazel tool verification
- **scripts/tests/test-resources.sh**: System resource checks (disk space, memory)
- **scripts/tests/test-build.sh**: C++23 compilation and Bazel build system tests

### Benefits of Streamlined Testing

- **Focused Scope**: Tests only what's needed for C++23 Bazel development
- **Fast Execution**: Minimal overhead with targeted test categories
- **Clear Feedback**: Immediate validation of C++23 and Bazel setup
- **Easy Debugging**: Isolated test categories for quick issue identification
- **Maintainable**: Simple, focused scripts that are easy to understand and modify

## Notes

- The container uses GCC 13 as the default compiler for optimal C++23 support
- Uses modern Bazel MODULE system (Bzlmod) instead of legacy WORKSPACE
- MODULE.bazel is automatically initialized if not present
- .bazelrc is configured with C++23 flags, Bzlmod, and optimization settings
