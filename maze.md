# CS50 Maze Challenge Project for Team Teraflop

## Michael Canche, CS50 Winter 2020

### maze

A maze is a data structure that manages a 2-Dimensional array that containts open paths,
walls, and avatars. The maze is capable of holding any variable of avatars.
This data structure is meant to display the maze and keep track of walls. 
Exact positions of avatars are not readily available, as we assume the program that is using this
data structure has access to all these positions.

Cells contain the value, which is the avatar Id, at the point, and whether the cardinal directions are blocked.

### Usage
See maze.h for functions
If two or more avatars overlap, the maze will only display the avatar that arrived at the position first.
Proper usage will show the avatar that remains on the position.
If avatars move together, the first one to move will appear in the maze.

Add gui.a or use maze.o when compiling

Flow:  
Initialize:  
maze_new  

For each avatar:  
maze_updateDirection  
maze_update  
maze_print  
maze_delete  


### Implementation
The maze_t structure contains the 2-Dimensional array (which contains cells), the max width, max height,
number of avatars, and direction of the next avatar. 
Within each cell in the 2-Dimensional array, the key is:  
-1  = open path  
0  = avatar  
1  = avatar  
...

Cells are printed as:  
-1 = *  
0  = 0  
1  = 1  
...

Walls are printed as "||" for east and west walls and "-" for north and south walls.

### Assumptions

Assumes that maze is used after a connection with the server has been made and avatar positions have been collected.
Assumes that the user will call freeing functions at the end of usage.
Due to the maze being used after calling the server, we assume any positions given are within the maze boundaries.
    We check maze boundaries when evaluating if a wall has been found.

### Compilation

To compile, simply `make`.

