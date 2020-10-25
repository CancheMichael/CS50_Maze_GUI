# Makefile for Maze Challenge - Teraflop
#   Builds and compiles all these utility functions into a library.
#
#
# Michael Canche, February 2020

# object files, and the target library
OBJS = maze.o gtkGUI.o
LIB = gui.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
CC = gcc
MAKE = make

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
maze.o: maze.h
gtkGUI.o: gtkGUI.h

.PHONY: clean sourcelist gtkGUI guiTesting all

gtkGUI:
	$(CC) $(CFLAGS) -o gtkGUITesting gtkGUITesting.c gui.a

guiTesting: 
	$(CC) $(CFLAGS) -o guiTesting guiTesting.c gui.a
	
# list all the sources and docs in this directory.
# (this rule is used only by the Professor in preparing the starter kit)
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f gtkGUITesting
	rm -f guiTesting
