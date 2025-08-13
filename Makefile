.PHONY: build run clean verbose v

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
  ECHO_PREFIX =
else
  BAZEL_VERBOSE_FLAGS =
  ECHO_PREFIX = @
endif

verbose:
	@targets='$(filter-out $@,$(MAKECMDGOALS))'; \
	if [ -z "$$targets" ]; then targets=build; fi; \
	echo "(Re-invoking with VERBOSE=1) -> $$targets"; \
	$(MAKE) VERBOSE=1 $$targets

# Short alias: `make v build` or just `make v`
v: verbose

# Build the project (use `make verbose build` for verbose output)
build:
	@echo "Building project... (verbose=$(VERBOSE))"
	$(ECHO_PREFIX)bazel build $(BAZEL_VERBOSE_FLAGS) //...

# Run the main application
run: build
	@echo "Running main application... (verbose=$(VERBOSE))"
	$(ECHO_PREFIX)bazel run $(BAZEL_VERBOSE_FLAGS) //src:main

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	bazel clean