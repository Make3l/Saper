#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "logic.h"

int X = 0, Y = 0;

void test_initSize() {
    initSize(1);
    assert(X == 9 && Y == 9);

    initSize(2);
    assert(X == 16 && Y == 16);

    initSize(3);
    assert(X == 30 && Y == 16);

    printf("test_initSize passed!\n");
}

void test_checkAround() {
    X = 5;
    Y = 5;
    char map[25] = {
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, MINE,  EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY,  EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, MINE, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    };

    int count = checkAround(map, 2, 2);
    assert(count == 2);

    count = checkAround(map, 4, 4);
    assert(count == 1);

    count = checkAround(map, 0, 0);
    assert(count == 1);

    printf("test_checkAround passed!\n");
}

void test_setFields() {
    X = 5;
    Y = 5;
    char map[25] = {
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, MINE,  EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, MINE,  EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    };

    setFields(map);

    assert(map[1 * X + 1] == MINE);
    assert(map[2 * X + 2] == MINE);
    assert(map[0 * X + 0] == '1');
    assert(map[2 * X + 1] == '2');

    printf("test_setFields passed!\n");
}

void test_outsideBox() {
    X = 5;
    Y = 5;
    int result = outsideBox(7, 1, 1);
    assert(result == 0);

    result = outsideBox(0, 1, 1);
    assert(result == 0);

    printf("test_outsideBox passed!\n");
}

void test_getMap() {
    X = 5;
    Y = 5;
    char *map = getMap(5, 1, 1, 0);

    int mine_count = 0;
    for (int i = 0; i < X * Y; i++) {
        if (map[i] == MINE)
            mine_count++;
    }
    assert(mine_count == 5);

    free(map);
    printf("test_getMap passed!\n");
}

int main() {
    test_initSize();
    test_checkAround();
    test_setFields();
    test_outsideBox();
    test_getMap();

    printf("All tests passed!\n");
    return 0;
}