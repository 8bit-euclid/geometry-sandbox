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
    # C++ development tools (clang/clang++ support)
    clang-18 \
    clangd-18 \ 
    libc++-18-dev \
    libc++abi-18-dev \
    lldb \ 
    # C++ development tools (gcc/g++ support)
    build-essential \
    gcc-13 \
    g++-13 \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Set clang-18 as default C/C++ compiler
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-18 100 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-18 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100

# Set environment variables for Clang and Bazel
ENV CC=/usr/bin/clang-18 \
    CXX=/usr/bin/clang++-18 \
    BAZEL_USE_CPP_ONLY_TOOLCHAIN=1

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
