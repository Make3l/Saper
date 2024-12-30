#include "logic.h"

int main()
{
    int gameType = 0, x = 5, y = 5, xType, yType, counter;
    char input;
    int gameOver = 1;

    char *map = NULL;
    char *userMap = NULL;

    printf("Give me map size: ");
    scanf("%d", &gameType);

    printf("Give me start input: ");
    scanf("%d %d", &x, &y);

    if (gameType < 3)
        gameInit(gameType);
    else
    {
        printf("what kind of grid woud u like: ");
        scanf("%d %d", &xType, &yType);
        gameInitUnique(xType, yType);
    }

    map = getMap(X * Y * 0.15, y, x);
    userMap = getUserMap(map, y, x);
    show(userMap);

    while (gameOver)
    {

        printf("Give me your move (f/r x y): ");
        scanf(" %c %d %d", &input, &x, &y);

        if (input == 'f')
        {
            setValue(userMap, y, x, FLAG);
        }
        else if (input == 'r')
        {
            if (userMap[y * Y + x] == FLAG)
            {
                setValue(userMap, y, x, TYLE);
            }
            else if (map[y * Y + x] == MINE)
            {
                printf("Game over with score %d\n", counter);
                break;
            }
            else
            {
                counter++;
                swapValues(map, userMap, y, x);
            }
        }
        else
        {
            printf("Invalid input\n");
            continue;
        }

        system("clear");

        printf("\n");
        show(userMap);
        printf("\n");
        show(map);
        printf("\n");

        if (counter >= Y * X - (Y * X * 0.15))
            gameOver = 0;
    }

    return 0;
}