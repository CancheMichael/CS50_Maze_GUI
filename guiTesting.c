/*
   File: guiTesting.c

   Description: Simple file to showcase usage of maze, as well as
   to test for error.

   Compile: mygcc `pkg-config --cflags gtk+-3.0` -o guiTesting guiTesting.c `pkg-config --libs gtk+-3.0` gui.a

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
#include <stdarg.h>
#include "maze.h"
#include <netinet/in.h>
//#include <gtk/gtk.h>
//#include "gtkGUI.c"
#include <pthread.h>
int main(int argc, char *argv[]) {
    //Boundaries
    int maxX = 4;
    //int sleepTimer = 1;
    int maxY = 6;
    //Creating avatars
    int buffer = 1;
    Avatar *av1 = calloc(buffer, sizeof(Avatar));
    Avatar *av2 = calloc(buffer, sizeof(Avatar));
    Avatar *av3 = calloc(buffer, sizeof(Avatar));
    //Set id for avatars
    av1->id = 1;
    av2->id = 2;
    av3->id = 0;
    //Set starting positions
    av1->pos.x = 2;
    av1->pos.y = 0;
    av2->pos.x = 3;
    av2->pos.y = 4;
    av3->pos.x = 1;
    av3->pos.y = 1;
    //Creates new maze with boundaries and 2 avatars
    maze_t *mz = maze_new(maxX, maxY, 2);
    //pthread_t t1;
    //pthread_create(&t1, NULL, renderMaze, NULL);
    //sleep(7);
    
    //updateMaze(mz);
    //Update direction and avatars
    maze_updateDirection(mz, 8);
    maze_update(mz, av2);
    maze_updateDirection(mz, 8);
    maze_update(mz, av1);
    maze_updateDirection(mz, 8);
    maze_update(mz, av3);

    //Prints starting positions
    maze_print(mz, 1, stdout);
        //sleep(sleepTimer);

    //GTK gui
    //Change positions
    //This is testing jumping, for error checking
    //This is not how the actual maze will be used
    av1->pos.x = 3;
    av1->pos.y = 4;
    maze_updateDirection(mz, 8);
    maze_update(mz, av1);
        //updateMaze(mz);

    maze_print(mz, 2, stdout);
        //sleep(sleepTimer);

    maze_updateDirection(mz, 8);
    maze_update(mz, av2);
        //updateMaze(mz);

    maze_print(mz, 3, stdout);
        //sleep(sleepTimer);

    maze_updateDirection(mz, 1);
    maze_update(mz, av1);
        //updateMaze(mz);

    maze_print(mz, 4, stdout);
        //sleep(sleepTimer);

    maze_updateDirection(mz, 8);
    maze_update(mz, av2);
        //updateMaze(mz);

    maze_print(mz, 5, stdout);
        //sleep(sleepTimer);

    //Testing avatars following the leader
    av2->pos.x = 2;
    av2->pos.y = 4;
    av1->pos.x = 2;
    av1->pos.y = 4;
    maze_updateDirection(mz, 0);
    maze_update(mz, av1);
        //updateMaze(mz);

    maze_print(mz, 6, stdout);
        //sleep(sleepTimer);

    maze_updateDirection(mz, 0);
    maze_update(mz, av2);
        //updateMaze(mz);

    maze_print(mz, 7, stdout);
        //sleep(sleepTimer);

    //Leaving the leader
    maze_updateDirection(mz, 8);
    maze_update(mz, av1);
        //updateMaze(mz);

    maze_print(mz, 8, stdout);
    maze_updateDirection(mz, 1);
    av2->pos.x = 2;
    av2->pos.y = 3;
    maze_update(mz, av2);
    //updateMaze(mz);

    maze_print(mz, 9, stdout);
        //sleep(sleepTimer);

    //Testing hitting a wall
    maze_updateDirection(mz, 0);
    maze_update(mz, av1);
    //updateMaze(mz);

    maze_print(mz, 10, stdout);
        //sleep(sleepTimer);

    maze_updateDirection(mz, 1);
    maze_update(mz, av2);
    //updateMaze(mz);
    maze_print(mz, 11, stdout);
        //sleep(sleepTimer);

    //Remember to delete maze after use
        //pthread_join(t1, NULL);

    maze_delete(mz);
    //Freeing avatar
    free(av1);
    free(av2);
    free(av3);
}