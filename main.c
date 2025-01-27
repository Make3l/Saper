#include "logic.h"
#include "output.h"

int main(int argc,char **argv)
{
    int difLevel = 1, y = 5, x = 5, counter = 1;
    char input;
    int gameOver = 0;
    int gameFromFile=0;

    FILE *in=NULL;
    char *map = NULL;
    char *userMap = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
        case 'f': // Flaga -f z nazwą pliku
            in = fopen(optarg, "r");
            if (!in) {
                perror("Error opening file");
                return -1;
            }
            gameFromFile = 1;
            break;
        default: // Nieznana flaga
            fprintf(stderr, "Usage: %s [-f filename]\n", argv[0]);
            return -1;
        }
    }
    
    if(gameFromFile==0)
    {
        printf("Enter game level\n1 - easy  2 - medium  3 - hard  4 - custom: ");
        scanf("%d", &difLevel);
    }
    else
    {
        fscanf(in,"%d", &difLevel);
    }
    
        

    if (difLevel > 4)
        return -1;

    if(gameFromFile==1 && difLevel==4)
        fscanf(in,"%d %d",&Y,&X);
    else
        initSize(difLevel);

    char *tempMap = initMap();

    show(tempMap);
    free(tempMap);
    tempMap = NULL;

    if(gameFromFile==1)
    {
        fscanf(in,"%d %d", &x, &y);
    }
    else
    {
        printf("Give me start input: ");
        scanf("%d %d", &x, &y);
    }


    if (y < 0 || x < 0 || y >= X || x >= Y)
        return -1;

    map = getMap(difLevel < 3 ? Y * X * 0.15 : Y * X * 0.20, x, y,(gameFromFile==1? 0:1));
    userMap = getUserMap(map, x, y);
    show(userMap);

    counter = checkFields(map, x, y);
    int max_points=Y * X - (difLevel < 3 ? X * Y * 0.15 : X * Y * 0.20);
    while (!gameOver)
    {
        if(gameFromFile==1)
        {
            if (fscanf(in," %c %d %d", &input, &x, &y) != 3 || (y < 0 || x < 0 || y >= X || x >= Y))
            {
                printf("\n Invalid input. Please enter a character followed by two integers.\n");
                continue;
            }
        }
        else
        {
            printf("Your score: %d\n", counter*difLevel);
            printf("Give me your move (f/r y x): ");
            if (scanf(" %c %d %d", &input, &x, &y) != 3 || (y < 0 || x < 0 || y >= X || x >= Y))
            {
                printf("\n Invalid input. Please enter a character followed by two integers.\n");
                continue;
            }
        }


        switch (input)
        {
        case 'f':
            if (userMap[x * X + y] == TILE)
            {
                setValue(userMap, x, y, FLAG);
            }
            break;

        case 'r':
            if (userMap[x * X + y] == FLAG)
            {
                setValue(userMap, x, y, TILE);
            }
            else if (map[x * X + y] == MINE)
            {
                gameOver = 1;
                continue;
            }
            else if (userMap[x * X + y] == TILE)
            {
                counter++;// nie tylko jak jest tile, wiec warunki gry trzeba zmienic troche
                swapValues(map, userMap, x, y);
            }
            break;

        default:
            printf("Invalid input\n");
            continue;
        }

        system("clear");
        printf("\n");
        show(userMap);
        printf("\n");
        show(map);
        printf("\n");
        if (counter >= max_points) // jeszcze - puste pola aaa i mozna boostowac wynik zakladajasz sztuczne flagi
            gameOver = 1;
    }
    if(gameFromFile==1)
    {
        printf("%d %d %d",counter, counter * difLevel,counter*difLevel>=max_points?1:0);
        return 0;
    }
        
    if(counter*difLevel<max_points)
        printf("Game over with score %d\n", counter * difLevel);
    else
        printf("You are a bomb expert, congrats! Game won with score %d\n", counter * difLevel);
    if(gameFromFile==1)
        printf("Nmber of correct steps:%d\n",counter);
    char name[100];
    printf("Enter your nick:");
    scanf("%s",name);
    updateBestPlayers(name, counter * difLevel);

    fclose(in);
    return 0;
}