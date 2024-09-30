# Directory Structure (`ds`)

![GitHub release (latest by date)](https://img.shields.io/github/v/release/Deyan2306/ds) ![GitHub all releases](https://img.shields.io/github/downloads/Deyan2306/ds/total) ![GitHub](https://img.shields.io/github/license/Deyan2306/ds) ![GitHub last commit](https://img.shields.io/github/last-commit/Deyan2306/ds) ![GitHub issues](https://img.shields.io/github/issues/Deyan2306/ds)

A lightweight and fast CLI tool written in C++ that lists and manages files in a directory structure. The tool allows recursive iteration, detailed file information, and customized display with several flags.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Flags](#flags)
- [Examples](#examples)
- [Build](#build)
- [License](#license)

## Features

- **Recursive Directory Traversal**: Traverse directories recursively with the `-r` flag.
- **File Information**: Get detailed information about file permissions, ownership, size, and modification time with the `-l` flag.
- **Hidden Files**: List hidden files (starting with `.`) with the `-a` flag.
- **Directory-only View**: List only directories with the `-d` flag.
- **Human-readable Size**: Display file sizes in a human-readable format with the `-m` flag.
- **No Icons**: Disable icons for directories with the `-x` flag.

## Installation

### Prerequisites

Ensure you have the following dependencies installed:

- C++ compiler (GCC/Clang)
- Boost Filesystem Library
- Boost Program Options Library

### From Source

To install the tool, clone the repository and build the project:

```bash
git clone https://github.com/Deyan2306/ds.git
cd ds
make
```

To install the tool globally:

```bash
sudo make install
```

To uninstall:

```bash
sudo make uninstall
```

## Usage

Run the `ds` command followed by optional flags to list files in a directory.

```bash
ds [options]
```

If no path is provided, the tool defaults to the current working directory.

### Flags

The following flags can be passed to customize the output:

| Flag                | Description                                                        |
|---------------------|--------------------------------------------------------------------|
| `-h, --help`        | Show help message and usage.                                        |
| `-p, --path`        | Specify the path to the directory (default is current directory).   |
| `-a, --all`         | Show hidden files.                                                 |
| `-l, --long`        | Show detailed information including permissions, owner, size, etc. |
| `-r, --recursive`   | Recursively list files and directories.                            |
| `-m, --human_readable` | Show sizes in human-readable format (e.g., KB, MB).              |
| `-d, --directories_only` | Only display directories in the output.                       |
| `-x, --no_icons`    | Do not display icons for directories.                              |

## Examples

- **Basic Listing**:
    ```bash
    ds
    ```
    Lists all files and directories in the current directory.

- **List with Hidden Files**:
    ```bash
    ds -a
    ```

- **List with Detailed Information**:
    ```bash
    ds -l
    ```

- **Recursive Listing**:
    ```bash
    ds -r
    ```

- **Human-Readable Sizes**:
    ```bash
    ds -l -m
    ```

### Command Chaining
You could also chain commands like so:
```
ds -lamx
```

## Build

You can modify the project or rebuild it by using the provided `Makefile`.

To clean up the build:
```bash
make clean
```

To build and install the project:
```bash
make
sudo make install
```

To uninstall:
```bash
sudo make uninstall
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.