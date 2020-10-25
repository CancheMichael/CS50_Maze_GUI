/*
   File: maze.c

   Description: The job of the maze is to be manage a struct that stores and receives the current
   position of the avatars, and can update a visual representation of the maze.
   Usage is detailed in maze.h

   Author: Michael Canche, February 2020

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../amazing.h"
#include "maze.h"
#include <stdarg.h>

/**************** global types ****************/

typedef struct maze {  
    int xSize; //Max size of the x axis
    int ySize; //Max size of the y axis
    int numOfAvatars; //Number of avatars
    int direction; //Direction of next avatar move
    cell_t **mazeAr; //Array holding the maze and positions
    
} maze_t;

//Checks if point is within bounds
bool withinBounds(maze_t *maze, int x, int y);

//Return xSize: max width
int getXSize(maze_t *maze) {
  return maze->xSize;
}

//Return ySize: max height
int getYSize(maze_t *maze) {
  return maze->ySize;
}

//Return the number of avatars in the maze
int getNumOfAvatars(maze_t *maze) {
  return maze->numOfAvatars;
}

//Return the current direction that the next avatar should go
int getMazeDirection(maze_t *maze) {
  return maze->direction;
}

//Returns the maze array
cell_t** getMazeArray(maze_t *maze) {
  return maze->mazeAr;
}

//Helper method for update_maze
void checkLocationsInMaze(maze_t *maze, int i, int j);

/**************** maze_new() ****************/
/* see maze.h for description */
maze_t * maze_new(int maxX, int maxY, int numOfAvatars) {
  maze_t *maze = calloc(1, sizeof(maze_t) + sizeof(cell_t)*maxX*maxY);
  if (maze == NULL) {
    return NULL;              // error allocating maze
  } else {
    // initialize contents of maze structure
    maze->xSize = maxX;
    maze->ySize = maxY;
    maze->numOfAvatars = numOfAvatars;
    maze->direction = 9; //Starter value
    maze->mazeAr = calloc(maxY, sizeof(cell_t*));
    for(int i = 0; i < maxY; i++) {
      maze->mazeAr[i] = calloc(maxX, sizeof(cell_t));
    }
    for(int i = 0; i < maze->ySize; i++) {
      for(int j = 0; j < maze->xSize; j++) {
        maze->mazeAr[i][j].value = -1;
      }
    }
    return maze;
  }
}

/**************** maze_update() ****************/
/* see maze.h for description */
//We assume the number of avatars passed does not change
void maze_update(maze_t *maze, Avatar *av) {
  //Error checking
  if(maze != NULL && av != NULL) {
    //Due to the structure being held by col, row
    //We must swap x and y
    int realX = av->pos.x;
    int realY = av->pos.y;
    av->pos.x = realY;
    av->pos.y = realX;
  //Iterate through given arguments 
    for(int i = 0; i < maze->ySize; i++) {
      //Check column twice for the avatar
      //Once to see if it is alone
      //A second time to see if it is with a leader
      bool foundAvatar = false;
      for(int j = 0; j < maze->xSize; j++) {
        cell_t mazeSpot = maze->mazeAr[i][j]; 
        //If avatar did not move
        if(mazeSpot.value == av->id && i == (int)(av->pos.x) && j == (int)(av->pos.y)) {
            checkLocationsInMaze(maze, i, j);
            foundAvatar = true;
        }
        //If move was successful
        else if(mazeSpot.value == av->id) {
            maze->mazeAr[i][j].value = -1;
        }
      }
      if(foundAvatar) {
        for(int j = 0; j < maze->xSize; j++) {
          cell_t mazeSpot = maze->mazeAr[i][j]; 
          //If avatar did not move
          if(mazeSpot.value >= 0 && mazeSpot.value == maze->mazeAr[(int)(av->pos.x)][(int)(av->pos.y)].value) {
            checkLocationsInMaze(maze, i, j);
          }
          //If move was successful
          else if(mazeSpot.value == av->id) {
              maze->mazeAr[i][j].value = -1;
          }
        }
      }
    }
    if(maze->mazeAr[(int)(av->pos.x)][(int)(av->pos.y)].value == -1) {
      maze->mazeAr[(int)(av->pos.x)][(int)(av->pos.y)].value = av->id;
    }
    //Swap back
    av->pos.x = realX;
    av->pos.y = realY;
  }
  
}


/**************** maze_updateDirection() ****************/
/* see maze.h for description */
void maze_updateDirection(maze_t *maze, int dir) {
  //Error checking
  if(maze != NULL) {
    maze->direction = dir;
  }
}

/**************** maze_delete() ****************/
/* see maze.h for description */
void maze_delete(maze_t *maze) {
  //Null checks
  if(maze != NULL) {
    //Free all rows
    for(int i = 0; i < maze->ySize; ++i) {
        free(maze->mazeAr[i]);
    }
    //Free all columns
    free(maze->mazeAr);
    //Free the entire maze
    free(maze);
  }
}

/**************** maze_print() ****************/
/* see maze.h for description */
void maze_print(maze_t *maze, int turnID, FILE *fp) {
  //Null checks
  if (fp != NULL) {
    if (maze != NULL) {  
        printf("Turn: %d", turnID);
        //Iterates through each element in the array
        for(int i = 0; i < maze->ySize; i++) {
          fprintf(fp, "\n");
          for(int j = 0; j < maze->xSize; j++) {
            cell_t mazeSpot = maze->mazeAr[i][j];
            if(mazeSpot.westBlocked) { //West Wall
              fprintf(fp, "|");
            }
            else {
              fprintf(fp, " ");
            }
            if(mazeSpot.value >= 0) { //Avatar
              fprintf(fp, "%d", mazeSpot.value);
            }
            else if (mazeSpot.value == -1){ //Open Path
              fprintf(fp, "*");
            }
            if(mazeSpot.eastBlocked) { //East Wall
              fprintf(fp, "|");
            }
            else {
              fprintf(fp, " ");
            }
            
          }
          fprintf(fp, "\n");
          for(int j = 0; j < maze->xSize; j++) {
            cell_t mazeSpot = maze->mazeAr[i][j];
            if(mazeSpot.southBlocked) { //North Wall
              fprintf(fp, " - ");
            }
            else {
              fprintf(fp, "   ");
            }
          }
      }
      fprintf(fp, "\n");
    } 
    else {
      fprintf(fp, "(null)\n");  
    }
  }
}

//Checks if point is within bounds
bool withinBounds(maze_t *maze, int x, int y) {
  //Due to how the maze is initialized, x and y are swapped
  if(x >= 0 && y >= 0 && x < maze->ySize && y < maze->xSize) {
    return true;
  }
  return false;
}

void checkLocationsInMaze(maze_t *maze, int i, int j) {
  //Check if the direction is valid
  //If valid, add a wall
  if(maze->direction == 0) { //West Blocked - East Wall
    if(withinBounds(maze, i, j-1)) {
      maze->mazeAr[i][j-1].eastBlocked = true;
      maze->mazeAr[i][j].westBlocked = true;
    }
  }
  else if(maze->direction == 1) { //North Blocked - South Wall
    if(withinBounds(maze, i-1, j)) {
      //Due to the way the graphic interface works,
      //When North is blocked, the cell above the current cell
      //Must be updated
      maze->mazeAr[i][j].northBlocked = true;
      maze->mazeAr[i-1][j].southBlocked = true;
    }
  }
  else if(maze->direction == 2) { //South Blocked - North Wall
    if(withinBounds(maze, i+1, j)) {
      maze->mazeAr[i+1][j].northBlocked = true;
      maze->mazeAr[i][j].southBlocked = true;
    }
  }
  else if(maze->direction == 3) { //East Blocked - West Wall
    if(withinBounds(maze, i, j+1)) {
      maze->mazeAr[i][j+1].westBlocked = true;
      maze->mazeAr[i][j].eastBlocked = true;
    }
  }
}
