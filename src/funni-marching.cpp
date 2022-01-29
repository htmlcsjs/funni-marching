#include "raylib.h"
#include <iostream>

int main(void)
{
    // Const and Var declaration
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Window initlisation
    InitWindow(screenWidth, screenHeight, "funni march");
    SetTargetFPS(150);

    while (!WindowShouldClose())
    {
        /* Main loop */


        /* Drawing */
        BeginDrawing();

        ClearBackground(GetColor(0x069420));
        DrawFPS(10, 10);

        for (size_t i = 0; i < 10; i++)
        {
            DrawLine((screenWidth/10)*i, 0, (screenWidth/10)*i, screenHeight, WHITE);
            DrawLine(0, (screenHeight/10)*i, screenWidth, (screenHeight/10)*i, WHITE);
        }
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}