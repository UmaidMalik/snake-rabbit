#ifndef TIMER_H
#define TIMER_H

typedef struct
{
    float dt;
    float time_accumulated;
    float interval;
    float current_time;
    float rabbit_move_time_accum;
    float rabbit_interval;
    float interval_scale;
} Timer;

void timer_update(Timer* t);

#endif