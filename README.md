# Maze Solver

## Overview

This project implements a program to solve mazes using **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** algorithms. It defines a grid-based maze structure where cells can be open or blocked, and provides visual feedback for solving the maze using a graphics library.

## Features

- **Maze Input:** The maze is read from a file, with walls represented as `@` and open paths as `-`.
- **Algorithms:** 
  - **Breadth-First Search (BFS):** Finds the shortest path in the maze.
  - **Depth-First Search (DFS):** Explores paths deeply before backtracking.
- **Visualization:** Displays the maze and highlights the solution path graphically.
- **Validation:** Ensures the solution path is valid (no loops, proper start and end, valid moves).

---

## File Structure

### Source Files
- **`maze.cpp`**: Contains the main logic for solving mazes, including:
  - Pathfinding algorithms (BFS and DFS).
  - Helper functions for validating paths and generating valid moves.
- **`mazegraphics.cpp`**: Implements the graphical display of the maze and solution path.
- **`main.cpp`**: Entry point for the program, reads maze files, and runs the solvers.

### Resource Files
- **Maze files (`res/*.maze`):** Define the maze structure. Example:
  ```
  @---@
  -@-@-
  @---@
  ```

---

## How to Use

### Prerequisites

- **C++ Compiler:** Ensure you have a modern C++ compiler (e.g., `g++`).
- **Libraries:** Include the required graphics and utility libraries (e.g., `gwindow`, `grid`, `queue`, `stack`).

### Building the Project

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd maze-solver
   ```
2. Compile the source code:
   ```bash
   g++ -o maze_solver main.cpp maze.cpp mazegraphics.cpp -std=c++17 -I<path-to-headers>
   ```

### Running the Program

1. Place your maze file in the `res/` folder.
2. Run the executable:
   ```bash
   ./maze_solver
   ```
3. Modify the maze file path in `main.cpp` as needed:
   ```cpp
   string mazeFile = "res/your-maze-file.maze";
   ```

---

## Input File Format

- Walls: `@`
- Open paths: `-`
- Example:
  ```
  @---@
  -@-@-
  @---@
  ```

---

## Output

1. **Console:**
   - Prints the path for both BFS and DFS in the format:
     ```
     r0c0 -> r1c0 -> ...
     ```
2. **Graphics:**
   - Displays the maze and highlights the solution path in red.

---

## Key Functions

### `maze.cpp`

- **`generateValidMoves(Grid<bool>& maze, GridLocation cur)`**:
  Generates all valid neighboring moves from the current location.

- **`validatePath(Grid<bool>& maze, Vector<GridLocation>& path)`**:
  Validates if a given path is a proper solution.

- **`solveMazeBFS(Grid<bool>& maze)`**:
  Uses BFS to find the shortest path.

- **`solveMazeDFS(Grid<bool>& maze)`**:
  Uses DFS to explore paths deeply before backtracking.

### `mazegraphics.cpp`

- **`drawMaze(const Grid<bool>& g)`**:
  Draws the maze structure graphically.

- **`highlightPath(Vector<GridLocation>& path, string color, int msecsToPause)`**:
  Highlights the solution path on the maze.

---

## Example

### Input Maze File

```
---@-
@-@@-
---@-
```

### Console Output

```
BFS Path:
r0c0 -> r0c1 -> r1c1 -> r2c1 -> r2c2 -> r2c3

DFS Path:
r0c0 -> r0c1 -> r1c1 -> r2c1 -> r2c2 -> r2c3
```

---

## Future Enhancements

- Add support for larger mazes.
- Implement additional pathfinding algorithms (e.g., A*).
- Enhance graphics for better interactivity.

---

## Author

**Joseph Le**  
10-07-24
