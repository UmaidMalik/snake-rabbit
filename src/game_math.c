#include "game_math.h"
#include <math.h>
#include <stdlib.h>

int game_math_mod(int a, int b)
{
    int r = a % b;
    return (r < 0) ? r + abs(b) : r;
}