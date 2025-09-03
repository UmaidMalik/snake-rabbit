#include "snake.h"
#include "game.h"
#include "game_math.h"

void InitSnake(Snake* snake)
{
    snake->body[0].x = 10;
    snake->body[0].y = GRID_HEIGHT / 2;
    snake->length = INIT_SNAKE_SIZE;
    snake->dir = EAST;
}

void BindSnakeTexture(Snake* snake, Texture texture)
{
    snake->texture = texture;
}

void MoveSnake(Snake* snake)
{
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->dir) {
        case NORTH:
            snake->body[0].y = game_math_mod((int)(snake->body[0].y - 1.0f), GRID_HEIGHT);
            break;
        case SOUTH:
            snake->body[0].y = game_math_mod((int)(snake->body[0].y + 1.0f), GRID_HEIGHT);
            break;
        case WEST:
            snake->body[0].x = game_math_mod((int)(snake->body[0].x - 1.0f), GRID_WIDTH);
            break;
        case EAST:
            snake->body[0].x = game_math_mod((int)(snake->body[0].x + 1.0f), GRID_WIDTH);
            break;
    }
}

void SetSnakeDirection(Snake* snake, Direction direction)
{
    if (
        (snake->dir == NORTH && direction == SOUTH)
        || (snake->dir == SOUTH && direction == NORTH)
        || (snake->dir == WEST && direction == EAST)
        || (snake->dir == EAST && direction == WEST)
    ) {
        return;
    }
    snake->dir = direction;
}

bool HasSnakeCollided(Snake* snake)
{
    Vector2 head = snake->body[0];

    // if snake collided with boundary
    /*if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT)
    {
        return true;
    }*/

    // if snake collided with its body
    if (snake->length > 4)
    {
        for (int i = 1; i < snake->length; i++)
        {
            if ((head.x == snake->body[i].x) && (head.y == snake->body[i].y))
            {
                return true;
            } 
        }
    }  
    return false;
}

void SnakeEatsFood(Snake* snake)
{
    snake->length += 1;
}

void RenderSnake(Snake* snake)
{
    DrawTexture(snake->texture, TILE_SIZE * snake->body[0].x, TILE_SIZE * snake->body[0].y, GOLD);
    for (int i = 1; i < snake->length; i++)
    {
        DrawTexture(snake->texture, TILE_SIZE * snake->body[i].x, TILE_SIZE * snake->body[i].y, VIOLET);
    }
}