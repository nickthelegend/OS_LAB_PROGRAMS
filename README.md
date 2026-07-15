# OS Lab Programs

> A collection of Operating Systems lab exercises written in C — CPU scheduling, file-handling system calls, and deadlock avoidance.

## Overview

This repository holds coursework for an Operating Systems lab, implemented as small, self-contained C programs. Each program demonstrates a core OS concept from first principles: how the CPU scheduler orders processes, how programs interact with files through low-level POSIX system calls, and how the Banker's algorithm keeps a system in a safe state. The code is intentionally simple and readable, meant for learning and reference rather than production use.

## Features

- **CPU scheduling algorithms** (`Question 1/`) — implementations that compute waiting time, turnaround time, and their averages for:
  - First Come First Serve (FCFS)
  - Shortest Job First (SJF)
  - Round Robin (with a configurable time quantum)
  - Priority scheduling
- **File-handling system calls** (`Question 2/`) — small demos of POSIX I/O:
  - `open`/`read`/`write` file copy
  - `fcntl` file-descriptor duplication
  - `lseek` file-pointer positioning
  - `stat` for file metadata (size, modification time)
  - directory listing via `opendir`/`readdir` (a minimal `ls`)
- **Deadlock avoidance** (`Question 3/`) — the Banker's algorithm, taking process/resource matrices as input and checking for a safe execution sequence, with resource request and release handling.

## Tech Stack

- **Language:** C
- **Standard library:** `<stdio.h>`, plus POSIX headers `<fcntl.h>`, `<unistd.h>`, `<sys/stat.h>`, `<dirent.h>` for the system-call demos
- **Toolchain:** GCC (prebuilt `.exe` binaries in this repo were compiled on Windows/MinGW)

## Getting Started

You need a C compiler such as `gcc`. Compile and run any program individually:

```bash
# CPU scheduling example
gcc "Question 1/1.fcfs.c" -o fcfs
./fcfs

# System-call example (POSIX / Linux / macOS / MinGW)
gcc "Question 2/1.openread.c" -o openread
./openread

# Banker's algorithm (reads process/resource data from stdin)
gcc "Question 3/1.BankersAlgorithimforDeadLockavoidance.c" -o bankers
./bankers
```

The scheduling programs use hard-coded sample process data; the Banker's algorithm prompts for input at runtime. Note that the file-handling demos expect their input files (e.g. `source.txt`, `file.txt`) to exist in the working directory.

## Project Structure

```
.
├── Question 1/   # CPU scheduling: FCFS, SJF, Round Robin, Priority
├── Question 2/   # File system calls: open/read, fcntl, lseek, stat, ls
└── Question 3/   # Banker's algorithm for deadlock avoidance
```

---

Built by [nickthelegend](https://github.com/nickthelegend) · [nickthelegend.tech](https://nickthelegend.tech)
