#include <iostream>
#include <raylib.h>
#include <vector>

#include "2D/Line.hpp"

// Const and Var declaration
const int screenWidth = 1280;
const int screenHeight = 720;
const int gridSize = 100;
const Color gridColour = DARKBLUE;

std::vector<helpers2D::Line> gridlines;

void generateGrid()
{
    for (int x = screenWidth/2 + gridSize; x < screenWidth; x += gridSize)
    {
        gridlines.push_back(helpers2D::Line(x, 0, x, screenHeight, gridColour));
    }

    for (int x = screenWidth/2 - gridSize; x > 0; x -= gridSize)
    {
        gridlines.push_back(helpers2D::Line(x, 0, x, screenHeight, gridColour));
    }

    for (int y = screenHeight/2 + gridSize; y < screenHeight; y += gridSize)
    {
        gridlines.push_back(helpers2D::Line(0, y, screenWidth, y, gridColour));
    }

    for (int y = screenHeight/2 - gridSize; y > 0; y -= gridSize)
    {
        gridlines.push_back(helpers2D::Line(0, y, screenWidth, y, gridColour));
    }

    gridlines.push_back(helpers2D::Line(0, screenHeight/2, screenWidth, screenHeight/2, WHITE));
    gridlines.push_back(helpers2D::Line(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE));
}

int main(void)
{
    // Window initlisation
    InitWindow(screenWidth, screenHeight, "funni march");
    SetTargetFPS(150);
    generateGrid();
    
    while (!WindowShouldClose())
    {
        /* Main loop */


        /* Drawing */
        BeginDrawing();

        ClearBackground(GetColor(0x060600));
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