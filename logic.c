#include "logic.h"

void initSize(int difLevel)
{
    switch (difLevel)
    {
    case 1:
        X = 9;
        Y = 9;
        break;

    case 2:
        X = 16;
        Y = 16;
        break;

    case 3:
        X = 16;
        Y = 30;
        break;
    case 4:
        printf("Enter custom map lenght and width: ");
        scanf("%d %d", &X, &Y);
        break;

    default:
        fprintf(stderr, "Entered wrong level");
        break;
    }
}

int checkAround(char *map, int y, int x)
{
    int live_neighbors = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) // Skip the current cell
                continue;

            int ny = y + i;
            int nx = x + j;

            // Check bounds and count mines
            if (nx >= 0 && nx < Y && ny >= 0 && ny < X && map[ny * Y + nx] == MINE)
            {
                live_neighbors++;
            }
        }
    }

    return live_neighbors;
}

void setFields(char *map)
{
    for (int y = 0; y < X; y++)
    {
        for (int x = 0; x < Y; x++)
        {
            if (map[y * Y + x] != MINE)
            {
                map[y * Y + x] = '0' + checkAround(map, y, x); // Store as char
                if (map[y * Y + x] == '0')
                    map[y * Y + x] = EMPTY;
            }
        }
    }
}

char *getMap(int mines, int y, int x)
{
    char *map = calloc(X * Y, sizeof(char)); // Initialize map to zeros

    if (!map)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    srand(time(NULL));

    for (int i = 0; i < mines; i++)
    {
        int temp = rand() % (X * Y); // Ensure within bounds

        if (map[temp] != MINE && temp != y * Y + x)
        {
            map[temp] = MINE;
        }
        else
        {
            i--; // Retry if mine already placed
        }
    }

    setFields(map);

    return map;
}

char *initMap()
{
    char *map = calloc(X * Y, sizeof(char)); // Initialize map to zeros

    if (!map)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    memset(map, TILE, X * Y);
    return map;
}

char *getUserMap(char *map, int y, int x)
{
    char *userMap = initMap();

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // if (i == 0 && j == 0) // Skip the current cell
            //     continue;

            int ny = y + i;
            int nx = x + j;

            // Check bounds and count mines
            if (nx >= 0 && nx < Y && ny >= 0 && ny < X && map[ny * Y + nx] != MINE)
            {
                swapValues(map, userMap, ny, nx);
            }
        }
    }

    return userMap;
}

void show(char *map)
{
    printf("  ");
    for (int i = 0; i < Y + 2; i++)
    {
        printf("%c ", WALLS);
    }
    printf("\n");

    for (int y = 0; y < X; y++)
    {
        for (int x = 0; x < Y; x++)
        {
            if (x == 0)
                printf("%d %c ", y, WALLS);
            printf("%c ", map[y * Y + x]);
            if (x == Y - 1)
                printf("%c ", WALLS);
        }
        printf("\n");
    }

    printf("  ");

    for (int i = 0; i < Y + 2; i++)
    {
        printf("%c ", WALLS);
    }
    printf("\n    ");

    for (int i = 0; i < Y; i++)
    {
        printf("%d ", i);
    }

    printf("\n\n");
}

void swapValues(char *map, char *userMap, int y, int x)
{
    userMap[y * Y + x] = map[y * Y + x];
}

void setValue(char *userMap, int y, int x, char value)
{
    userMap[y * Y + x] = value;
}
