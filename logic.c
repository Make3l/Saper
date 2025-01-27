#include "logic.h"

void initSize(int difLevel)
{
    switch (difLevel)
    {
    case 1:
        Y = 9;
        X = 9;
        break;

    case 2:
        Y = 16;
        X = 16;
        break;

    case 3:
        Y = 16;
        X = 30;
        break;
    case 4:
        printf("Enter custom map lenght and width: ");
        scanf("%d %d", &Y, &X);
        break;

    default:
        fprintf(stderr, "Entered wrong level");
        break;
    }
}

int checkAround(char *map, int x, int y)
{
    int bombs = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) // Skip the current cell
                continue;

            int ny = x + i;
            int nx = y + j;

            // Check bounds and count mines
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && map[ny * X + nx] == MINE)
            {
                bombs++;
            }
        }
    }

    return bombs;
}

int checkFields(char *map, int x, int y)//returns number of fileds(do not count bombs)
{
    int fields = 1;//includes one that i am standing on

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) // Skip the current cell
                continue;

            int ny = x + i;
            int nx = y + j;

            // Check bounds and count mines
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && map[ny * X + nx] != MINE)
            {
                fields++;
            }
        }
    }

    return fields;
}

void setFields(char *map)
{
    for (int x = 0; x < Y; x++)
    {
        for (int y = 0; y < X; y++)
        {
            if (map[x * X + y] != MINE)
            {
                map[x * X + y] = '0' + checkAround(map, x, y); // Store as char
                if (map[x * X + y] == '0')
                    map[x * X + y] = EMPTY;
            }
        }
    }
}

int outsideBox(int tmp,int x,int y)
{
    if(tmp>=(x*X+y-X-1) && tmp <=(x*X+y-X+1))//gorna granica
        return 0;

    if(tmp>=(x*X+y-1) && tmp<=(x*X+y+1))//srodkowa granica
        return 0;

    if(tmp>=(x*X+y+X-1) && tmp <=(x*X+y+X+1))//dolna granica
        return 0;
    
    return 1;
}

char *getMap(int mines, int x, int y,int ifRand)
{
    char *map = calloc(Y * X, sizeof(char)); // Initialize map to zeros

    if (!map)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    if(ifRand==1)
        srand(time(NULL));
    else
        srand(1);

    for (int i = 0; i < mines; i++)
    {
        int temp = rand() % (Y * X); // Ensure within bounds

        if (map[temp] != MINE && outsideBox(temp,x,y))
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
    char *map = calloc(Y * X, sizeof(char)); // Initialize map to zeros

    if (!map)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    memset(map, TILE, Y * X);
    return map;
}

char *getUserMap(char *map, int x, int y)
{
    char *userMap = initMap();

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // if (i == 0 && j == 0) // Skip the current cell
            //     continue;

            int nx = x + i;
            int ny = y + j;

            // Check bounds and count mines
            if (ny >= 0 && ny < X && nx >= 0 && nx < Y && map[nx * X + ny] != MINE)
            {
                swapValues(map, userMap, nx, ny);
            }
        }
    }

    return userMap;
}

void show(char *map)
{
    for (int i = 0; i < X+2; i++)
    {
        printf("%c ", WALLS);
    }
    printf("\n");

    for (int x = 0; x < Y; x++)
    {
        for (int y = 0; y < X; y++)
        {
            if (y == 0)
                printf("%c ", WALLS);

            printf("%c ", map[x * X + y]);

            if (y == X - 1)
                printf("%c ", WALLS);
        }
        printf("\n");
    }


    for (int i = 0; i < X + 2; i++)
    {
        printf("%c ", WALLS);
    }
    printf("\n    ");


    printf("\n\n");
}

void swapValues(char *map, char *userMap, int x, int y)
{
    userMap[x * X + y] = map[x * X + y];
}

void setValue(char *userMap, int x, int y, char value)
{
    userMap[x * X + y] = value;
}
