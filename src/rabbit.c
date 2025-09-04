#include "rabbit.h"
#include "game_math.h"

void RabbitInit(Rabbit* rabbit)
{
    rabbit->position = CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
}

void RabbitBindTexture(Rabbit* rabbit, Texture texture)
{
    rabbit->texture = texture;
}

void RabbitRender(Rabbit* rabbit)
{
    DrawTexture(rabbit->texture, TILE_SIZE * rabbit->position.x, TILE_SIZE * rabbit->position.y, WHITE);
}

void RabbitResetLocation(Rabbit* rabbit, Snake* snake)
{
    int max_tries = 10000;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        flag = false;
        rabbit->position = CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
        for (int i = 0; i < snake->length; i++)
        {
            if (rabbit->position.x == snake->body[i].x && rabbit->position.y == snake->body[i].y)
            {
                flag = true;
                break;
            }   
        }
        count++;
    }
}

void RabbitMove(Rabbit* rabbit,  Snake* snake)
{
    int max_tries = 50;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        int dx = GetRandomValue(-1, 1);
        int dy = GetRandomValue(-1, 1);
        flag = false;
        rabbit->position.x = game_math_mod((int) (rabbit->position.x + dx), GRID_WIDTH);
        rabbit->position.y = game_math_mod((int) (rabbit->position.y + dy), GRID_HEIGHT);
        for (int i = 0; i < snake->length; i++)
        {
            if (rabbit->position.x == snake->body[i].x && rabbit->position.y == snake->body[i].y)
            {
                flag = true;
                break;
            }
        }
        count++;
    }
}