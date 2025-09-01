#ifndef TIMER_H
#define TIMER_H

typedef struct
{
    float dt;
    float time_accumulated;
    float interval;
    float current_time;
} Timer;

void timer_update(Timer* t);
void timer_set_interval(Timer* t, float interval);

#endif