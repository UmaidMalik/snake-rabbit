#include "game_math.h"
#include <math.h>
#include <stdlib.h>

int GameMath_Mod(int a, int b)
{
    int r = a % b;
    return (r < 0) ? r + abs(b) : r;
}