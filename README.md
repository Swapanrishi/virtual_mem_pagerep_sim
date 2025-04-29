
# 🧠 Virtual Memory Page Replacement Simulator (FLTK)

This project is a **C++ graphical simulation tool** for visualizing two key virtual memory page replacement algorithms — **FIFO (First-In First-Out)** and **LRU (Least Recently Used)** — using the **FLTK (Fast Light Toolkit)** GUI library.

## 📋 Features

- Simulates **FIFO** and **LRU** page replacement algorithms
- Interactive GUI to enter page sequences and frame size
- Displays step-by-step results and total page faults
- Built with C++ and FLTK for cross-platform lightweight UI

## 📸 GUI Overview

- `Frame Size`: Number of frames in physical memory
- `Page Sequence`: A sequence of integers (page numbers)
- `Algorithm`: Choice between FIFO and LRU
- `Run Simulation`: Executes the selected algorithm
- `Clear`: Resets inputs and output display

## 🛠️ Technologies Used

- **Language**: C++
- **GUI Library**: FLTK (Fast Light Toolkit)
- **Data Structures**: `std::set`, `std::queue`, `std::list`, `std::unordered_map`

## 🧪 Sample Input

- Frame Size: `3`
- Page Sequence: `7 0 1 2 0 3 0 4`

## 📥 Build Instructions

### Prerequisites
- C++ compiler (`g++`)
- FLTK library installed (`fltk-config`)

### Compile
```bash
g++ VirtualMemorySimulator_FLTK.cpp -o vmsim `fltk-config --cxxflags --ldflags`
