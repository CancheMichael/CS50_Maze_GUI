# CS50 Maze Challenge Project for Team Teraflop

## Michael Canche, CS50 Winter 2020

### gtkGUI

The gtkGUI program handle displaying the maze created using maze.c using the gtk graphics library.
Within gtk, the cairo library creates the shapes used.

Cells contain the value, which is the avatar Id, at the point, and whether the cardinal directions are blocked.

### Usage
See maze.h for functions
If two or more avatars overlap, the maze will only display the avatar that arrived at the position first.
Proper usage will show the avatar that remains on the position.
If avatars move together, the first one to move will appear in the maze.

Add gui.a or use maze.o when compiling

Flow:  
Initialize:  
maze_new - from maze.h  
renderMaze - create this using a thread  

For each avatar:  
maze_updateDirection - from maze.h  
maze_update - from maze.h  
updateMaze  
maze_delete  


### Implementation
gtkGUI iterates through the maze data structure, printing a white rectangle for an open space,
a colored rectangle for an avatar, and horizontal or vertical lines for walls.
The starting window size is 800x800, and the size of the rectangles adjust to this starting size.



### Assumptions

Same assumptions found in maze.md

### Compilation

To compile, simply mygcc `pkg-config --cflags gtk+-3.0` -o mainPgrm mainPgrm.c `pkg-config --libs gtk+-3.0` gui.a  
Where mainPgrm is a program that will use gtkGUI.
