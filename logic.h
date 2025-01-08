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

int Y, X;//Y-poziomo(kolumny)  X-pionowo(wiersze)

void initSize(int difLevel);
int checkAround(char *map, int x, int y);
void setFields(char *map);
char *getMap(int mines, int x, int y);
char *initMap(); // Initialize the map for the first display
int outsideBox(int tmp,int x,int y);
char *getUserMap(char *map, int x, int y);
void show(char *map);
void swapValues(char *map, char *userMap, int x, int y);
void setValue(char *userMap, int x, int y, char value);

#endif // MAP_H