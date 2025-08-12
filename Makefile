.PHONY: build run clean

# Default target
all: build

# Build the project
build:
	@echo "Building project..."
	bazel build //...

# Run the main application
run: build
	@echo "Running main application..."
	bazel run //src:main

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	bazel clean