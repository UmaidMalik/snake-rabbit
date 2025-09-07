#pragma once

#ifndef WINDOW_SETTING_H
#define WINDOW_SETTING_H

#include <stdint.h>

typedef struct
{
    const char* title;
    uint32_t grid_width;
    uint32_t grid_height;
    uint32_t tile_size;
    uint32_t fps;
    uint32_t bottom_ui_height;
    uint32_t bottom_ui_y_offset;
    uint32_t bottom_ui_text_height;
    uint32_t screen_width;
    uint32_t screen_height;
} WindowSetting;

void WindowSetting_Init(WindowSetting* ws);
void WindowSetting_Setup();

#endif
/*
#define GAME_SCORE (game->snake->length - INIT_SNAKE_SIZE)
*/