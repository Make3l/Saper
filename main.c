#include "logic.h"

int main()
{
    int difLevel = 1, y = 5, x = 5, counter = 0;
    char input;
    int gameOver = 0;

    char *map = NULL;
    char *userMap = NULL;

    printf("Enter game level\n1 - easy  2 - medium  3 - hard  4 - custom: ");
    scanf("%d", &difLevel);

    if (difLevel > 4)
        return -1;

    initSize(difLevel);

    char *tempMap = initMap();

    show(tempMap);
    free(tempMap);
    tempMap = NULL;

    printf("Give me start input: ");
    scanf("%d %d", &x, &y);

    if (y < 0 || x < 0 || y >= X || x >= Y)
        return -1;

    map = getMap(difLevel < 3 ? Y * Y * 0.15 : Y * Y * 0.20, x, y);
    userMap = getUserMap(map, x, y);
    show(userMap);

    counter = 9 - checkAround(map, x, y);

    while (!gameOver)
    {
        printf("Your score: %d\n", counter*difLevel);
        printf("Give me your move (f/r y x): ");
        if (scanf(" %c %d %d", &input, &x, &y) != 3 || (y < 0 || x < 0 || y >= Y || x >= Y))
        {
            printf("\n Invalid input. Please enter a character followed by two integers.\n");
            continue;
        }

        switch (input)
        {
        case 'f':
            if (userMap[x * Y + y] == TILE)
            {
                setValue(userMap, x, y, FLAG);
            }
            break;

        case 'r':
            if (userMap[x * Y + y] == FLAG)
            {
                setValue(userMap, x, y, TILE);
            }
            else if (map[x * Y + y] == MINE)
            {
                gameOver = 1;
                continue;
            }
            else if (userMap[x * Y + y] == TILE)
            {
                counter++;
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
        if (counter >= Y * Y - (difLevel < 3 ? Y * Y * 0.15 : Y * Y * 0.20)) // jeszcze - puste pola aaa i mozna boostowac wynik zakladajasz sztuczne flagi
            gameOver = 1;
    }
    if(!gameOver)
        printf("Game over with score %d\n", counter * difLevel);
    else
        printf("You are a bomb expert, congrats! Game won with score %d\n", counter * difLevel);

    return 0;
}