#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Constants
#define MINE '@'
#define EMPTY ' '
#define FLAG '&'
#define TILE '#'
#define WALLS '*'

int X, Y;

void initSize(int difLevel);
int checkAround(char *map, int y, int x);
void setFields(char *map);
char *getMap(int mines, int y, int x);
char *initMap(); // Initialize the map for the first display
char *getUserMap(char *map, int y, int x);
void show(char *map);
void swapValues(char *map, char *userMap, int y, int x);
void setValue(char *userMap, int y, int x, char value);

#endif // MAP_H