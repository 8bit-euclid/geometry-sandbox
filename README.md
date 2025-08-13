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

## License

See `LICENSE`.