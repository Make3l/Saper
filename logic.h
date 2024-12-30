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
#define TYLE '#'
#define WALLS '*'

int X ,Y; 

void gameInit(int gameType);
void gameInitUnique(int x, int y); // Custom grid

int checkAround(char *map, int y, int x);
void setFields(char *map);
char *getMap(int mines, int y, int x);
char *getUserMap(char *map, int y, int x);
void show(char *map);
void swapValues(char *map, char *userMap, int y, int x);
void setValue(char *userMap, int y,int x, char value);

#endif // MAP_H