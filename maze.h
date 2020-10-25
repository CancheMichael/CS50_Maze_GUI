/* 
 * maze.h - header file for Maze Challenge maze module
 *
 * A "maze" is a matrix created using a pointer to a pointer.
 * The maze is filled with keys, which are described in the README.md
 * 
 * Michael Canche, February 2020
 */

#ifndef __MAZE_H
#define __MAZE_H

#include <stdio.h>
#include <stdbool.h>
#include "../amazing.h"

/**************** global types ****************/
typedef struct cell {  
  int value;
  bool northBlocked;
  bool southBlocked;
  bool westBlocked;
  bool eastBlocked;
  /*  Maze Key
        -1 = Empty/Accessible path
        0 = Avatar
        # >= 0 = Avatar
        ...
        Wall are displayed within a cell
  */
} cell_t;
typedef struct cell cell_t;  // opaque to users of the module
typedef struct maze maze_t;  // opaque to users of the module

/**************** functions ****************/

/**************** getXSize ****************/
/* Get size of x axis.
 *
 * We return:
 *   the max size of the x axis.
 */
int getXSize(maze_t *maze);

/**************** getNumOfAvatars ****************/
/* Get number of avatars.
 *
 * We return:
 *   the number of avatars.
 */
int getNumOfAvatars(maze_t *maze);

/**************** getYSize ****************/
/* Get size of y axis.
 *
 * We return:
 *   the max size of the y axis.
 */
int getYSize(maze_t *maze);

/**************** getMazeDirection ****************/
/* Get current maze direction the avatars.
 *
 * We return:
 *   the current maze direction for the avatars.
 */
int getMazeDirection(maze_t *maze);

/**************** getYSize ****************/
/* Get maze array.
 *
 * We return:
 *   the maze array.
 */
cell_t** getMazeArray(maze_t *maze);

/**************** maze_new ****************/
/* Create a new maze structure.
 *
 * We return:
 *   pointer to a new maze; NULL if error. 
 * We guarantee:
 *   mazeAr is filled. 
 * Caller is responsible for:
 *   later calling maze_delete();
 */
maze_t * maze_new(int maxX, int maxY, int numOfAvatars);

/**************** maze_update ****************/
/* Update the maze with new avatar positions.
 * 
 * Caller provides:
 *   valid pointer to maze,
 *   all avatars.
 * We guarantee:
 *   That the updated maze is printed.
 * We do:
 *  ignore if maze is NULL or av is NULL.
 * We assume:
 *  before every maze_update call, there is a call to
 *  maze_updateDirection
 */
void maze_update(maze_t *maze, Avatar *av);

/**************** maze_updateDirection() ****************/
/* Workaround method to build walls in maze_update
 * Updates direction which is stored in a maze
 * West  = 0
 * North = 1
 * South = 2
 * East  = 3
 */
void maze_updateDirection(maze_t *maze, int dir);

/**************** maze_print ****************/
/* Print tiles in the maze; provide the output file.
 *
 * Caller provides:
 *   valid pointer to maze, 
 *   FILE open for writing.
 *   Current turnId.
 * We print:
 *   Nothing if NULL fp. 
 *   "(null)" if NULL ctrs.
 *   otherwise, comma=separated list of key=counter pairs, all in {brackets}.
 */
void maze_print(maze_t *maze, int turnID, FILE *fp);


/**************** maze_delete ****************/
/* Delete the whole maze.
 *
 * Caller provides:
 *   a valid pointer to maze.
 * We do:
 *   we ignore NULL maze.
 *   we free all memory we allocate for this maze.
 */
void maze_delete(maze_t *maze);

#endif // __MAZE_H
