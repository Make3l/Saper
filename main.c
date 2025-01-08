#include "logic.h"

int main()
{
    int difLevel = 1, x = 5, y = 5, counter = 0;
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

    if (x < 0 || y < 0 || x >= Y || y >= X)
        return -1;

    map = getMap(difLevel < 3 ? X * Y * 0.15 : X * Y * 0.20, y, x);
    userMap = getUserMap(map, y, x);
    show(userMap);

    counter = 9 - checkAround(map, y, x);

    while (!gameOver)
    {
        printf("Your score: %d\n", counter);
        printf("Give me your move (f/r x y): ");
        if (scanf(" %c %d %d", &input, &x, &y) != 3 || (x < 0 || y < 0 || x >= Y || y >= X))
        {
            printf("\n Invalid input. Please enter a character followed by two integers.\n");
            continue;
        }

        switch (input)
        {
        case 'f':
            if (userMap[y * Y + x] == TILE)
            {
                setValue(userMap, y, x, FLAG);
            }
            break;

        case 'r':
            if (userMap[y * Y + x] == FLAG)
            {
                setValue(userMap, y, x, TILE);
            }
            else if (map[y * Y + x] == MINE)
            {
                gameOver = 1;
                continue;
            }
            else if (userMap[y * Y + x] == TILE)
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
        if (counter >= Y * X - (difLevel < 3 ? X * Y * 0.15 : X * Y * 0.20)) // jeszcze - puste pola aaa i mozna boostowac wynik zakladajasz sztuczne flagi
            gameOver = 1;
    }
    if(!gameOver)
        printf("Game over with score %d\n", counter * difLevel);
    else
        printf("You are a bomb expert, congrats! Game won with score %d\n", counter * difLevel);

    return 0;
}