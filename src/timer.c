#include "timer.h"
#include "raylib.h"

void timer_update(Timer* t)
{
    t->current_time = GetTime();
    t->dt = GetFrameTime();
    t->time_accumulated += t->dt;
    t->rabbit_move_time_accum += t->dt;
}
