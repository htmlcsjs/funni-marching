#include <iostream>
#include <raylib.h>
#include <vector>

#include "2D/Line.hpp"

int main(void)
{
    // Const and Var declaration
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int gridSize = 100;

    std::vector<helpers2D::Line> gridlines;    

    // Window initlisation
    InitWindow(screenWidth, screenHeight, "funni march");
    SetTargetFPS(150);

    for (int x = screenWidth/2; x < screenWidth; x += gridSize)
    {
        helpers2D::Line newLine = helpers2D::Line(x, 0, x, screenHeight, GREEN);
        gridlines.push_back(newLine);
    }

    for (int x = screenWidth/2; x > 0; x -= gridSize)
    {
        helpers2D::Line newLine = helpers2D::Line(x, 0, x, screenHeight, GREEN);
        gridlines.push_back(newLine);
    }

    for (int y = screenHeight/2; y < screenHeight; y += gridSize)
    {
        helpers2D::Line newLine = helpers2D::Line(0, y, screenWidth, y, GREEN);
        gridlines.push_back(newLine);
    }

    for (int y = screenHeight/2; y > 0; y -= gridSize)
    {
        helpers2D::Line newLine = helpers2D::Line(0, y, screenWidth, y, GREEN);
        gridlines.push_back(newLine);
    }
    
    while (!WindowShouldClose())
    {
        /* Main loop */


        /* Drawing */
        BeginDrawing();

        ClearBackground(GetColor(0x069420));
        DrawFPS(10, 10);
        
        for (auto& line : gridlines)
        {
            line.render();
        }
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}