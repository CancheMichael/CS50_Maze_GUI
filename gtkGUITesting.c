/*
   File: guiTestingTesting.c

   Description: Reads output from AMStartup while displaying the maze using gtk and cairo.

   Compile: mygcc `pkg-config --cflags gtk+-3.0` -o gtkGUITesting gtkGUITesting.c `pkg-config --libs gtk+-3.0` gui.a
   Usage:   ./gtkGUITesting pathToFile
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
#include <gtk/gtk.h>
#include "gtkGUI.h"
#include <pthread.h>

// ./gtkGUITesting fileName
int main(int argc, char *argv[]) {

    //Check arguments
    if(argc != 2) {
        fprintf(stderr, "Improper usage: ./gtkGUITesting fileName\n");
        return 1;
    }

    char *fileName = argv[1];
    FILE *fp;
    //If we can access the file
    if(access(fileName, R_OK) == 0) {
        fp = fopen(fileName, "r");
    }
    
    int buffer = 255;
    char line[buffer];
    //Ignore first two lines
    //If function is properly used
    fgets(line, buffer, fp);
    fgets(line, buffer, fp);
    //Get number of avatars
    fgets(line, buffer, fp);
    int numOfAvatars = atoi(line);
    //Get dimensions of maze
    fgets(line, buffer, fp);
    int x = -1;
    int y = -1;
    /* get the first token */
    char *num = strtok(line, " ");
    //Iterate through string
    while(num != NULL) {
        if(x == -1) {
            x = atoi(num);
        }
        else if(x != -1) {
            y = atoi(num);
        }
        num = strtok(NULL, " ");
    }

    //Create maze
    maze_t *mz = maze_new(x, y, numOfAvatars);
    pthread_t t1;
    pthread_create(&t1, NULL, renderMaze, NULL); 
    sleep(5);   
    //Iterate through the positions of the avatars
    int avX = 0;
    int avY = 0;
    while(fgets(line, buffer, fp)) {
        if(strcmp(line, "Maze Solved") == 0) {
            break;
        }
        //Create new avatar
        Avatar *av = calloc(1, sizeof(Avatar));
        char *num2 = strtok(line, " ");
        int tracker = 0;
        int avatarID = 0;  
        int direction = 9;
        bool lineRead = false;
        //Gets avatar parameters
        while(num2 != NULL) {
            if(tracker == 0) {
                avatarID = atoi(num2);
            }
            else if(tracker == 1) {
                direction = atoi(num2);
            }
            else if(tracker == 2) {
                avX = atoi(num2);
            }
            else if(tracker == 3) {
                avY = atoi(num2);
            }
            
            tracker++;
            lineRead = true;
            num2 = strtok(NULL, " ");
        }
        //If Avatar info successfully parsed
        if(lineRead) {
            av->id = avatarID;
            av->pos.x = avX;
            av->pos.y = avY;
            maze_updateDirection(mz, direction);
            maze_update(mz, av);
            updateMaze(mz);
        }
        
        free(av);
        //Sleeps to give the renderer time to display the maze at each step
        struct timespec seconds, nano;
        seconds.tv_sec  = 0;
        nano.tv_nsec = 200000000L;
        nanosleep(&seconds , &nano);
    }
    pthread_join(t1, NULL);
    maze_delete(mz);
}