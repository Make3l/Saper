#include "output.h"
#include <stdio.h>

void updateBestPlayers(char *name,int score)
{
    FILE *leader_board=fopen("leader_board.txt","r");
    if(leader_board==NULL)
    {
        fprintf(stderr,"Błąd wczytywania pliku");
    }

    board tab[5];
    char helper[10];
    for(int i=0;i<5;i++)
    {
        if(fscanf(leader_board,"%s %s %d",helper,tab[i].name,&tab[i].points)!=3)
        {
            printf("Błąd w %d iteracji",i);
        }
    }
    fclose(leader_board);



    leader_board=fopen("leader_board.txt","w");
    if(leader_board==NULL)
    {
        fprintf(stderr,"Błąd wczytywania pliku");
    }

    int i=0;
    while(tab[i].points>score && i<5)
    {
        fprintf(leader_board,"%d. %s %d\n",i+1,tab[i].name,tab[i].points);
        i++;
    }
    
    if(i<5)
    {
        fprintf(leader_board,"%d. %s %d\n",i+1,name,score);
        i++;
    }
    
    while(i<5)
    {
        fprintf(leader_board,"%d. %s %d\n",i+1,tab[i].name,tab[i].points);
        i++;
    }

    fclose(leader_board);

}