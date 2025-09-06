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

void WindowSetting_Init(WindowSetting* ws)
{
    ws->title = "Snake & Rabbit";
    ws->grid_width = 20;
    ws->grid_height = 15;
    ws->tile_size = 32;
    ws->fps = 60;

    ws->bottom_ui_height = 32;
    ws->bottom_ui_y_offset = 8;
    ws->bottom_ui_text_height = ws->bottom_ui_y_offset + ws->screen_height;

    ws->screen_width = ws->grid_width * ws->tile_size;
    ws->screen_height = ws->grid_height * ws->tile_size;
}

void WindowSetting_Setup()
{

}

#endif
/*
#define GAME_SCORE (game->snake->length - INIT_SNAKE_SIZE)
*/