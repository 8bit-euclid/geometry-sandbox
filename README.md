# Geometry Sandbox

Lightweight C++23 sandbox for experimenting with geometry / meshing ideas and integrating third‑party geometry libs (Eigen, Triangle, Geogram, CGAL, libigl, Pablo, OpenVDB).

## Prerequisites

- make
- Bazel (>= 8.x) installed & on PATH (invoked indirectly)
- A C++23 capable compiler (gcc >= 13 or clang >= 17 recommended)

## Workflow (Make Targets Only)

Quiet build (default):
```bash
make build
```

Run the demo (build if needed):
```bash
make run
```

Verbose build (show subcommands & failure details):
```bash
make verbose build        # or: make v build
```

Verbose run (verbose build + execute):
```bash
make verbose run          # or: make v run
```

Just `make verbose` (or `make v`) with no extra goal defaults to a verbose build.

Clean all Bazel artifacts:
```bash
make clean
```

Tip: You can chain, e.g. `make verbose run` for a one‑liner.

## Extending

Add new C++ sources / headers and expose them through a new or existing Bazel target; then invoke via the existing Make targets. If you add another binary (e.g. `//src:tool`), mirror the `run` rule pattern or create a small wrapper target + optional new phony make rule.

## IDE IntelliSense (compile_commands.json)

This repo integrates [hedron_compile_commands](https://github.com/hedronvision/bazel-compile-commands-extractor) to produce a `compile_commands.json` for accurate editor navigation/completion.

Generate / refresh it:

```bash
bazel build //... \
	--aspects=@hedron_compile_commands//:aspects.bzl%hedron_compile_commands_aspect \
	--output_groups=hedron_compile_commands

# Copy (or symlink) the generated file to project root for the C/C++ extension:
cp bazel-out/**/compile_commands.json ./compile_commands.json
```

(The wildcard path segment depends on your platform / Bazel output tree; use `find bazel-out -maxdepth 4 -name compile_commands.json` to locate it.)

VS Code is configured (`.vscode/settings.json`) to point to `compile_commands.json` when present.

## License

See `LICENSE`.