#include "logic.h"

int main()
{
    int difLevel = 1, x = 5, y = 5, xType, yType, counter;
    char input;
    int gameOver = 0;

    char *map = NULL;
    char *userMap = NULL;

    printf("Enter game level\n1 - easy  2 - medium  3 - hard  4 - custom: ");
    scanf("%d", &difLevel);
    
    initSize(difLevel);

    printf("Give me start input: ");
    scanf("%d %d", &x, &y);



    map = getMap(X * Y * 0.15, y, x);
    userMap = getUserMap(map, y, x);
    show(userMap);

    while (!gameOver)
    {

        printf("Give me your move (f/r x y): ");
        scanf(" %c %d %d", &input, &x, &y);

        switch(input)
        {
            case 'f':
                setValue(userMap, y, x, FLAG);
            break;

            case 'r':
                if (userMap[y * Y + x] == FLAG)
                {
                    setValue(userMap, y, x, TILE);
                }
                else if (map[y * Y + x] == MINE)
                {
                    gameOver = 1;
                }
                else if(userMap[y * Y + x] == TILE)
                {
                    counter++;
                    swapValues(map, userMap, y, x);
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
        if (counter >= Y * X - (Y * X * 0.15))//jeszcze - puste pola aaa i mozna boostowac wynik zakladajasz sztuczne flagi
            gameOver = 1;
    }
    printf("Game over with score %d\n", counter*difLevel);

    return 0;
}