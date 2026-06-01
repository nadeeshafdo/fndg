# fndg (Find 'n Grep)

A brutally fast, cross-platform CLI tool written in pure C that recursively searches through both filenames and file contents simultaneously.

It automatically skips binary files, ignores symlink loops, and color-codes the output to distinguish between name matches and content matches.

## Installation

### From Pre-compiled Binaries (Fastest)
Go to the [Releases](../../releases) tab and download the executable for your OS (Linux, macOS, or Windows). 
Put the binary in a directory that is in your system's `PATH`.

### From Source (Linux / macOS / Windows)
Requirements: `git`, `cmake` (3.10+), `gcc` or `clang`

```bash
git clone https://github.com/nadeeshafdo/fndg.git
cd fndg
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
```

## Usage

Search the current directory:

```bash
fndg "search_term"
```

Search a specific directory:

```bash
fndg "search_term" /path/to/dir
```

Check version:

```bash
fndg --version
```

## Architecture

* `src/` - Contains the modular C codebase (Main, Search, Traverse).
* `CMakeLists.txt` - CMake build configuration for cross-platform compilation.
* `build/` - Output directory for the compiled binary (generated after build).
* `.github/workflows/` - CI/CD pipeline for automated cross-platform releases.

## License

(c) 2026 nadeeshafdo
