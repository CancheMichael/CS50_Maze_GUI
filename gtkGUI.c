/*
   File: gtkGUI.c

   Description: Graphical interface for maze using GTK and Cairo
   To compile:  mygcc `pkg-config --cflags gtk+-3.0` -o guiTesting guiTesting.c `pkg-config --libs gtk+-3.0` gui.a
   Author: Michael Canche, February 2020

*/
#include <cairo.h>
#include <gtk/gtk.h>
#include "maze.h"
#include "../amazing.h"

static void drawMaze(cairo_t *);

maze_t *mz;
bool mazeLoaded = false;

//Called at a certain amount of ticks by the timer
//Used to refresh the image on the screen
static gboolean drawEvent(GtkWidget *widget, cairo_t *cr, gpointer userData) {
  drawMaze(cr);
  return FALSE;
}

//Draws the maze using the loaded maze structure
static void drawMaze(cairo_t *cr) {
    //If a maze has been loaded
    if(mazeLoaded) {
        //Sets default color to white
        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_set_line_width(cr, .5);
        int x = 0;  //Starting x for image
        int y = 0;  //Starting y for image
        int mazeWidth = getXSize(mz);
        int mazeColumn = getYSize(mz);
        cell_t **mzAr = getMazeArray(mz);
        int spot;   //Current position/cell in maze
        //Dictates how much x and y should move
        int nextStepX = (double)400 / mazeWidth;
        int nextStepY = (double)400 / mazeColumn;
        int rectangleScaler = 4;
            // Iterate through the matrix
            for (int i = 0; i < mazeColumn; i++){
                //printf("Row: %d\n", i);
                for (int j = 0; j < mazeWidth; j++){
                    cairo_set_source_rgb (cr, 0.5, 0.5, 1);
                    // Parse the 2D Array
                    spot = mzAr[i][j].value;
                    // Draw the open paths
                    cairo_set_source_rgb (cr, 1, 1, 1);
                    cairo_rectangle (cr, x + (nextStepX / rectangleScaler), 
                            y + (nextStepY / rectangleScaler), 
                            nextStepX - (nextStepX / rectangleScaler), 
                            nextStepY - (nextStepY / rectangleScaler));
                    cairo_fill (cr);
                    cairo_set_source_rgba (cr, 1, 1, 1, .5);
                    cairo_set_source_rgb (cr, 0, 0, 0);
                    //If wall is found in the current cell
                    if(mzAr[i][j].westBlocked) { //West Wall
                        cairo_move_to(cr, x, y + nextStepY);
                        cairo_line_to(cr, x, y + nextStepY * 1/4);
                        cairo_stroke(cr);
                    }
                    if(mzAr[i][j].southBlocked) { //North Wall
                        cairo_move_to(cr, x - nextStepX * 3/4, y + nextStepY);
                        cairo_line_to(cr, x, y + nextStepY);
                        cairo_stroke(cr);

                    }
                    if(mzAr[i][j].northBlocked) { //South Wall
                        cairo_move_to(cr, x + nextStepX * 3/4, y);
                        cairo_line_to(cr, x + nextStepX * 1/4, y);
                        cairo_stroke(cr);


                    }
                    if(mzAr[i][j].eastBlocked) { //East Wall
                        cairo_move_to(cr, x + nextStepX * 5/4, y + nextStepY);
                        cairo_line_to(cr, x + nextStepX * 5/4, y + nextStepY * 1/4);
                        cairo_stroke(cr);
                    }
                    //Open path
                    if (spot == -1) {
                        //printf("Found empty space");
                        x += nextStepX;
                    } 
                    //If an avatar is found
                    if (spot >= 0){
                        // Draw the avatar
                    cairo_set_source_rgb (cr, spot*.15+.1, spot*.1+.1, spot*.15+.1);
                    cairo_rectangle (cr, x + (nextStepX / rectangleScaler), 
                            y + (nextStepY / rectangleScaler), 
                            nextStepX - (nextStepX / rectangleScaler), 
                            nextStepY - (nextStepY / rectangleScaler));

                    cairo_fill (cr);
                    cairo_set_source_rgb (cr, 0, 0, 0);
                        //printf("Found avatar");
                        x += nextStepX;
                    }
                    x += nextStepX;
                    cairo_stroke(cr);
                }
                //Reset to start of row and move column
                x = 0;
                y += nextStepY;
                    
            }

        //cairo_stroke(cr);   
    } 
    //cairo_destroy(cr);
}

//Manages the timer widget
static gboolean timeHandler(GtkWidget *widget) {
    gtk_widget_queue_draw(widget);
    return TRUE;
}

void *renderMaze() {
    GtkWidget *window;
    GtkWidget *darea;
    
    gtk_init(0, NULL);
    //Creates a window, then adds a gtk drawing area to the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

    //Connects drawEvent with drawing area
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(drawEvent), NULL); 
    //Destroys window if window is closed
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
    //Timer
    g_timeout_add(1, (GSourceFunc) timeHandler, (gpointer) window);
    //Layout
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800); 
    gtk_window_set_title(GTK_WINDOW(window), "Maze");
    gtk_widget_show_all(window);
    gtk_main();
    //Memory Management
    g_object_unref (window);
    g_object_unref (darea);
    return NULL;
}

//Updates the loaded maze with the newly provided maze
void updateMaze(maze_t *maze) {
    mz = maze;
    mazeLoaded = true;
}