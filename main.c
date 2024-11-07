/*
 * https://github.com/acejacek/snowflake
 */

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define WIDTH 900
#define HEIGHT 900
#define SPEED 2.0f
#define RADIUS 3.0f
#define MAX_PARTICLES 10000

Vector2 particles[MAX_PARTICLES] = { 0 };
size_t count = 1;

Vector2 part = {.x = WIDTH/2.0f, .y = 0.0f};

void display(Vector2 p)
{
    Vector2 pp;
    for (int i = 0; i < 3; ++i)
    {
        p = Vector2Rotate(p, PI/3.0f);
        Vector2 r = Vector2Negate(p);   // mirrored point

        pp = (Vector2){
            .x = p.x + WIDTH/2.0f,
            .y = p.y + HEIGHT/2.0f
        };
        DrawCircleV(pp, RADIUS, WHITE);

        pp = (Vector2){
            .x = r.x + WIDTH/2.0f,
            .y = r.y + HEIGHT/2.0f
        };
        DrawCircleV(pp, RADIUS, WHITE);
    }
}

void draw_snowflake()
{
    for (size_t i = 1; i < count; ++i)
        display(particles[i]);
}

void new_particle()
{
    if (count >= MAX_PARTICLES) return;

    part.x -= SPEED;
    part.y += GetRandomValue(-RADIUS, RADIUS);

    int lock = 0;
    if (part.x <= 0.0f)
        lock = 1;

    // scan downwards, it's faster.
    // it's most likely, that colision will be with recently added particle
    for (size_t i = count - 1; (i != 0) && (!lock); --i)
        if (Vector2DistanceSqr(part, particles[i]) <= (RADIUS*2.0f)*(RADIUS*2.0f))
            lock = 1;

    if (lock)
    {
        particles[count++] = part;
        part = (Vector2){WIDTH/2.0f, 0.0f};
    }
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Brownian Tree Snowflake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
            IsKeyPressed(KEY_SPACE))
        {
            ClearBackground(BLACK);
            count = 1;
        }

        for (int i = 1; i < 100; ++i)
            new_particle();

        draw_snowflake();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
