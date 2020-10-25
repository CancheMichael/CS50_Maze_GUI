/* 
 * gtkGUI.h - header file for Maze Challenge gtk gui module
 *
 * The gtk gui module handles displaying the maze using the
 * gtk and cairo libraries.
 * 
 * Michael Canche, February 2020
 */

#ifndef __GTKGUI_H
#define __GTKGUI_H

#include <stdio.h>
#include <stdbool.h>
#include "../amazing.h"

/**************** functions ****************/

/**************** renderMaze ****************/
/* Starts the rendering maze process.
 *
 * The maze should be rendered using a thread.
 */
void *renderMaze();

/**************** renderMaze ****************/
/* Updates the maze structure that the graphics
 * renderer is using.
 *
 * We assume:
 *  The maze has been updated properly, as detailed
 *  in maze.md
 */
void updateMaze(maze_t *maze);

#endif // __GTKGUI_H
