# Intelligent Transport Network Management System (ITNMS)
**Data Structures & Algorithms (CS221) Final Project**

## 1. Project Overview
The ITNMS is a high-performance C++ application designed to simulate and optimize a city’s transport infrastructure. It handles route pathfinding, passenger ticketing, vehicle registration, and network metadata management. 

**Note:** This project is built using manual implementations of fundamental data structures. To meet academic requirements for memory management and algorithmic logic, no STL containers (like `std::vector` or `std::map`) were used.

## 2. Project Architecture & Modules
The project follows a modular, header-only design for the data structures to ensure clear separation of concerns.

### **Core Data Structures (Source Code)**
* **`Graph.h`**: Manages the transport network using an Adjacency List. Implements Dijkstra’s Algorithm, Prim’s MST, BFS/DFS, and Cycle Detection.
* **`BST.h`**: Stores station metadata (IDs/Names) in a Binary Search Tree for $O(\log N)$ searching.
* **`Hash.h`**: A vehicle database using a Hash Table with Separate Chaining to handle ID collisions.
* **`Heap.h`**: A Min-Heap implementation for prioritizing vehicle dispatching.
* **`Stack.h`**: An array-based Stack used to power the "Undo" functionality for network changes.
* **`Queue.h`**: A Linked-List based FIFO queue for passenger ticketing management.
* **`Sorting.h`**: A specialized utility containing 6 sorting algorithms (Quick, Merge, Heap, etc.) and search logic.

### **Main Drivers**
* **`main.cpp`**: An automated testing suite that validates all phases of the system, including edge cases.
* **`manualMain.cpp`**: A comprehensive, 31-option interactive menu for manual administration.

## 3. How to Run the Project

### **Compiling on Windows (MinGW/GCC)**
1. Open your terminal (CMD or PowerShell) in the project folder.
2. To run the **Automated Test Suite**:
   ```bash
   g++ main.cpp -o automated_test
   ./automated_test

3. To run the **Interactive Management System**:
   ```bash
   g++ manualMain.cpp -o itnms_app
   ./itnms_app

## 4. Key Features
* **Shortest Path Calculation:** Implements Dijkstra's algorithm to find the most efficient route between any two active stations based on edge weights.
* **Undo System:** Utilizes a LIFO Stack to track structural changes (like adding/removing routes), allowing administrators to revert the last action in $O(1)$ time.
* **Collision Handling:** Employs Separate Chaining in the Hash Table. This ensures that even if multiple vehicle IDs hash to the same index, data is preserved in a linked list.
* **Recursive BST Deletion:** Uses a robust recursive algorithm to remove station metadata while maintaining the Binary Search Tree property (handling 0, 1, or 2 child nodes).
* **Network Integrity:** Includes automated Cycle Detection and "Busiest Station" analytics to monitor network connectivity.

## 5. System Requirements
* **Compiler:** GCC 4.9+ or any C++11 (or higher) compatible compiler.
* **Operating System:** * **Windows 10/11:** Recommended for full UTF-8 symbol support in the CLI.
  * **Linux/Ubuntu:** Fully supported for core logic and performance testing.
* **Memory:** Minimal (Manual memory management ensures a small footprint < 10MB RAM).

## 6. Project Authors
* Syed Rayyan Hasan
* Syeda Fatima tu Zahra
* S