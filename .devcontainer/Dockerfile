FROM ubuntu:24.04

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Create workspace directory first
RUN mkdir -p /workspace

# Rename existing ubuntu user to vscode (UID/GID 1000 already exists)
RUN usermod -l vscode ubuntu \
    && groupmod -n vscode ubuntu \
    && usermod -d /home/vscode -m vscode

# Set ownership and permissions of workspace
RUN chown -R vscode:vscode /workspace \
    && chmod -R 755 /workspace

# Install essential packages for C++23 development
RUN apt-get update && apt-get install -y \
    # Basic tools
    sudo \
    curl \
    wget \
    git \
    # C++ development tools
    build-essential \
    gcc-13 \
    g++-13 \
    clang-18 \
    libc++-18-dev \
    libc++abi-18-dev \
    # Additional development tools
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Set GCC-13 as default (supports C++23)
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100

# Install Bazelisk as the Bazel binary (wrapper and version manager for Bazel)
RUN wget -O /usr/local/bin/bazel https://github.com/bazelbuild/bazelisk/releases/download/v1.26.0/bazelisk-linux-amd64 \
    && chmod +x /usr/local/bin/bazel

# Install Buildifier (Bazel BUILD file formatter and linter)
RUN wget -O /usr/local/bin/buildifier https://github.com/bazelbuild/buildtools/releases/latest/download/buildifier-linux-amd64 \
    && chmod +x /usr/local/bin/buildifier

# Add vscode user to sudo group
RUN usermod -aG sudo vscode \
    && echo 'vscode ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# Switch to vscode user
USER vscode
WORKDIR /workspace
