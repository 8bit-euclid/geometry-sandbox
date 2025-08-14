.PHONY: build run clean verbose v test help

# Default target
all: build

# Verbosity control (only via the phony 'verbose' target)
# Usage examples:
#   make verbose build       # verbose build
#   make verbose run         # verbose build + run
#   make verbose             # defaults to verbose build
# Implementation: 'verbose' re-invokes make with VERBOSE=1 for the remaining goals.
VERBOSE ?= 0

ifeq ($(VERBOSE),1)
  BAZEL_VERBOSE_FLAGS = --verbose_failures --subcommands
else
  BAZEL_VERBOSE_FLAGS =
endif

verbose:
	@targets='$(filter-out $@,$(MAKECMDGOALS))'; \
	if [ -z "$$targets" ]; then targets=build; fi; \
	echo "(Re-invoking with VERBOSE=1) -> $$targets"; \
	$(MAKE) VERBOSE=1 $$targets

# Build the project (use `make verbose build` for verbose output)
build:
	@echo "Building project... (verbose=$(VERBOSE))"
	bazel build $(BAZEL_VERBOSE_FLAGS) //...

# Run the main application
run: build
	@echo "Running main application... (verbose=$(VERBOSE))"
	bazel run $(BAZEL_VERBOSE_FLAGS) //src:main

# Run tests.
# Variables:
#   TEST_TARGETS   (default: //...) Bazel targets to test
#   TEST_FILTER    (optional) GoogleTest filter pattern (e.g., EigenSuite.*:TriangleSuite.*-TriangleSuite.SquareTriangulation)
#   SHOW_TESTS=1   Stream test output (see individual test status) instead of only on failure.
TEST_TARGETS ?= //...
TEST_FILTER ?=
SHOW_TESTS ?= 0

ifeq ($(strip $(TEST_FILTER)),)
	GTEST_FILTER_ARGS =
else
	# Pass filter to each test via --test_arg
	GTEST_FILTER_ARGS = --test_arg=--gtest_filter=$(TEST_FILTER)
endif

ifeq ($(SHOW_TESTS),1)
	TEST_OUTPUT_MODE = --test_output=streamed
else
	TEST_OUTPUT_MODE = --test_output=errors
endif

test:
	@echo "Running tests: targets=$(TEST_TARGETS) filter='$(TEST_FILTER)' show_tests=$(SHOW_TESTS) verbose=$(VERBOSE)"
	bazel test $(BAZEL_VERBOSE_FLAGS) $(TEST_TARGETS) $(GTEST_FILTER_ARGS) $(TEST_OUTPUT_MODE)

# Refresh compile_commands.json for clangd language server
compile_commands:
	@echo "Refreshing compile_commands.json..."
	bazel run @hedron_compile_commands//:refresh_all
	
# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	bazel clean
