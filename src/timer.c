#include "timer.h"
#include "raylib.h"

void timer_update(Timer* t)
{
    t->current_time = GetTime();
    t->dt = GetFrameTime();
    t->time_accumulated += t->dt;
}

void timer_set_interval(Timer* t, float interval)
{
    t->interval = interval;
}
