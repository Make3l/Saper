#ifndef _OUTPUT_H_
#define _OUTPUT_H_

typedef struct
{
    char name[50];
    int points;
}board;

void updateBestPlayers(char *name,int score);

#endif