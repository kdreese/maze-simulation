# Maze Simulation by Kyle Reese

A C++ Sample Project in which a cat and a mouse both traverse a maze in order to capture their lunch

* The mouse uses the A* pathfinding algorithm to get to the cheese.
* If the mouse is within the cat's line of sight, it will move towards it, otherwise it will move in a random available direction other than where it just came from

## How to Run
#### These instructions assume you are compiling in Windows and have Visual Studio installed with Desktop development with C++ checked. Otherwise, you can compile with your preferred compiler.
1. Navigate to the folder containing the project in a developer command line
2. Run `cl /EHsc maze-simulation.cpp` to compile the project
3. Run `maze-simulation.exe` to view the outcome of the simulation

## References
The A* code was built with reference to the [example code from geeksforgeeks.org](https://www.geeksforgeeks.org/a-search-algorithm/)
