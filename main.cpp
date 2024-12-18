#include "filelib.h"
#include "maze.h"
#include "mazegraphics.h"
using namespace std;

int main() {
    // Modify maze file here - see example mazes in res/ folder.
    // New maze files can be created using '-' and '@' like in the example files
    string mazeFile = "res/25x33.maze";
    Grid<bool> maze;
    readMazeFile(mazeFile, maze);

    Vector<GridLocation> soln1 = solveMazeBFS(maze); //BFS
    for (GridLocation i: soln1)
    {
        std::cout << i << ' ';
    }
    std::cout << endl;
    std::cout << "\n" << endl;

    Vector<GridLocation> soln2 = solveMazeDFS(maze); //DFS
    for (GridLocation i: soln2)
    {
        std::cout << i << ' ';
    }
    std::cout << endl;

    return 0;
}
