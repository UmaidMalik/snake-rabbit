#include "window_setting.h"

void WindowSetting_Init(WindowSetting* ws)
{
    ws->title = "Snake & Rabbit";
    ws->grid_width = 20;
    ws->grid_height = 15;
    ws->tile_size = 32;
    ws->fps = 60;

    ws->screen_width = ws->grid_width * ws->tile_size;
    ws->screen_height = ws->grid_height * ws->tile_size;

    ws->bottom_ui_height = 32;
    ws->bottom_ui_y_offset = 8;
    ws->bottom_ui_text_height = ws->bottom_ui_y_offset + ws->screen_height;
}