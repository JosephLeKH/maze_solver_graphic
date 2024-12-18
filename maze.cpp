/*******************************************************************
 * maze.cpp
 * Joseph Le
 * 10-07-24
 *
 * This program implements algorithms to solve mazes using both
 * Breadth-First Search (BFS) and Depth-First Search (DFS) methods.
 * It defines a grid-based maze structure where cells can be open
 * or blocked, represented using a `Grid<bool>` type.
 *
*******************************************************************/
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;


/*
 * This function takes a `Grid<bool>` representing a maze and the current location (`cur`)
 * of a player or entity within that maze. It returns a set of all valid neighboring
 * moves that can be made from the current location. The function checks the four possible
 * directions (up, down, left, right) from the current location and adds valid, open
 * neighbors to the returned set of locations.
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;
    GridLocation loc;
    int row = cur.row;
    int col = cur.col;

    // Check top
    if (row > 0)
    {
        loc = {row - 1, col};
        if (maze[loc])
        {
            neighbors.add(loc);
        }
    }

    // Check bottom
    if (row < maze.numRows() - 1)
    {
        loc = {row + 1, col};
        if (maze[loc])
        {
            neighbors.add(loc);
        }
    }

    // Check left
    if (col > 0)
    {
        loc = {row, col - 1};
        if (maze[loc])
        {
            neighbors.add(loc);
        }
    }

    //Check right
    if (col < maze.numCols() - 1)
    {
        loc = {row, col + 1};
        if (maze[loc])
        {
            neighbors.add(loc);
        }
    }
    return neighbors;
}

/*
 * This function validates a given path in a maze to ensure it is a valid solution.
 * The function performs the following checks:
 * 1. The path must start at the top-left corner (0, 0) and end at the bottom-right corner
 *    of the maze (maze.numRows() - 1, maze.numCols() - 1).
 * 2. Each move in the path must be to a valid neighboring location, where neighboring
 *    means adjacent cells that are open.
 * 3. The path should not revisit any location (no loops).
 */
void validatePath(Grid<bool>& maze, Vector<GridLocation>& path) {
    if (path.isEmpty()) {
        error("Path is empty!");
    }

    /* If you find a problem with the path, call error() to report it.
     * If the path is a valid solution, then this function should run to completion
     * without raising any errors.
     */
    Set<GridLocation> set;
    Set<GridLocation> validSet;
    GridLocation start = {0, 0};
    GridLocation end = {maze.numRows() - 1, maze.numCols() - 1};
    GridLocation temp;

    set.add(path.get(0));
    validSet = generateValidMoves(maze, path.get(0));

    if (path.get(0) != start || path.get(path.size() - 1) != end)
    {
        error("The start or ending location is not correct.");
    }

    for(int i = 1; i < path.size(); i++)
    {
        temp = path.get(i);
        if (set.contains(temp))
        {
            error("There's a loop in the path.");
        }
        else if (!validSet.contains(temp))
        {
            error("There's an unvalid move in the vector.");
        }
        else
        {
            // Update for the next valid moves
            set.add(temp);
            validSet = generateValidMoves(maze, temp);
        }
    }
}

/*
 * The function maintains a queue to store paths being explored and uses the
 * generateValidMoves helper function to find valid neighboring locations.
 *
 * The BFS algorithm ensures that the shortest path is found by exploring all
 * neighbors at the present depth before moving on to nodes at the next depth level.
 * When the end location is reached, the path is returned. If no path exists,
 * an empty vector is returned.
 */
Vector<GridLocation> solveMazeBFS(Grid<bool>& maze) {
    Vector<GridLocation> path;
    Queue<Vector<GridLocation>> allPaths;
    Grid<bool> newMaze = maze;
    GridLocation end = {maze.numRows() - 1, maze.numCols() - 1};
    GridLocation start = {0, 0};
    GridLocation lastLoc;

    drawMaze(maze);

    // Initialize the queue
    path.add(start);
    allPaths.enqueue(path);

    while(!allPaths.isEmpty())
    {
        // Get the front path vector
        path = allPaths.dequeue();
        lastLoc = path.get(path.size() - 1);

        highlightPath(path, "red", 10);

        if (lastLoc == end)
        {
            return path;
        }
        else
        {
            // For every valid move, move there and add the move to the path.
            // No double backing or looping moves
            for (GridLocation temp: generateValidMoves(maze, lastLoc))
            {
                if (temp != lastLoc && newMaze[temp])
                {
                    newMaze[temp] = false;
                    Vector<GridLocation> newPath = path;
                    newPath.add(temp);
                    allPaths.enqueue(newPath);
                }
            }
        }
    }

    return path;
}

/*
 * The DFS algorithm dives deep into each path before backtracking, ensuring
 * that it exhausts one route before trying alternative routes. When the end
 * location is reached, the complete path is returned. If no path exists,
 * an empty vector is returned.
 */
Vector<GridLocation> solveMazeDFS(Grid<bool>& maze) {
    Vector<GridLocation> path;
    Stack<Vector<GridLocation>> allPaths;
    Grid<bool> newMaze = maze;
    GridLocation end = {maze.numRows() - 1, maze.numCols() - 1};
    GridLocation start = {0, 0};
    GridLocation lastLoc;

    drawMaze(maze);

    // Initialize the stack
    path.add(start);
    allPaths.push(path);

    while(!allPaths.isEmpty())
    {
        // Get the back path vector
        path = allPaths.pop();
        lastLoc = path.get(path.size() - 1);

        highlightPath(path, "red", 10);

        if (lastLoc == end)
        {
            return path;
        }
        else
        {
            // For every valid move, move there and add the move to the path.
            // No double backing or looping moves
            for (GridLocation temp: generateValidMoves(maze, lastLoc))
            {
                if (temp != lastLoc && newMaze[temp])
                {
                    newMaze[temp] = false;
                    Vector<GridLocation> newPath = path;
                    newPath.add(temp);
                    allPaths.push(newPath);
                }
            }
        }
    }

    return path;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines = stringSplit(readEntire(in), '\n');

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Vector<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}
