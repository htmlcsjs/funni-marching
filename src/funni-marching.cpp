#include <charconv>
#include <iostream>
#include <raylib.h>
#include <vector>

#include "2D/Line.hpp"
#include "2D/GridRectangle.hpp"

// Const and Var declaration
const int fps = 150;
const int scrollSpeed = 4;
const Color gridColour = DARKBLUE;

std::vector<helpers2D::Line> gridlines;
Vector2 gridSize;
unsigned int unitSize = 100;

// Resources
extern const unsigned char _binary_resources_logo_png_start, _binary_resources_logo_png_end;
size_t logo_png_size = &_binary_resources_logo_png_end - &_binary_resources_logo_png_start;

void generateGrid()
{
    int screenX = GetScreenWidth();
    int screenY = GetScreenHeight();

    for (int x = screenX/2 + unitSize; x < screenX; x += unitSize)
    {
        gridlines.push_back(helpers2D::Line(x, 0, x, screenY, gridColour));
        gridSize.x++;
    }

    for (int x = screenX/2 - unitSize; x > 0; x -= unitSize)
    {
        gridlines.push_back(helpers2D::Line(x, 0, x, screenY, gridColour));
    }

    for (int y = screenY/2 + unitSize; y < screenY; y += unitSize)
    {
        gridlines.push_back(helpers2D::Line(0, y, screenX, y, gridColour));
        gridSize.y++;
    }

    for (int y = screenY/2 - unitSize; y > 0; y -= unitSize)
    {
        gridlines.push_back(helpers2D::Line(0, y, screenX, y, gridColour));
    }

    gridlines.push_back(helpers2D::Line(0, screenY/2, screenX, screenY/2, WHITE));
    gridlines.push_back(helpers2D::Line(screenX/2, 0, screenX/2, screenY, WHITE));
}

int main(void)
{
    // Window initlisation
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(768, 576, "funni march");
    SetTargetFPS(fps);
    generateGrid();
    unsigned long frameCount;

    // Set window icon
    Image icon = LoadImageFromMemory(".png", &_binary_resources_logo_png_start, logo_png_size);
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);
    UnloadImage(icon);

    helpers2D::GridRectangle selectionRectangle = helpers2D::GridRectangle(1.5, 1.5, 1, 1, YELLOW, unitSize);
    
    while (!WindowShouldClose())
    {
        /* Main loop */

        // Selection rect pos update
        const int selRectSpeed = fps / 10;

        bool keyDownRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
        bool keyDownLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        bool keyDownUp = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
        bool keyDownDown = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);

        Vector2 selRectPos = selectionRectangle.getGridPos();
    
        // we do a little if statmenting
        if (keyDownDown && frameCount % selRectSpeed == 0)
        {
            selRectPos.y -= 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }
        else if (keyDownUp && frameCount % selRectSpeed == 0)
        {
            selRectPos.y += 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }
        if (keyDownLeft && frameCount % selRectSpeed == 0)
        {
            selRectPos.x -= 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }
        else if (keyDownRight && frameCount % selRectSpeed == 0)
        {
            selRectPos.x += 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }

        // check for scroll changes and change zoom
        float scrolled = GetMouseWheelMove();
        if (scrolled != 0.0f && unitSize + scrolled * scrollSpeed > 0)
        {
            unitSize += scrolled * scrollSpeed;
            gridSize = (Vector2){0,0};
            gridlines.clear();
            generateGrid();
            selectionRectangle = helpers2D::GridRectangle(selRectPos, (Vector2){1,1}, YELLOW, unitSize);
        }
        
        // regen grid if window is resized
        if (IsWindowResized())
        {
            gridSize = (Vector2){0,0};
            gridlines.clear();
            generateGrid();
            selectionRectangle.setGridPos(selRectPos);
        }
        

        /* Drawing */
        BeginDrawing();

        ClearBackground(GetColor(0x060600));
        
        for (auto& line : gridlines)
        {
            line.render();
        }
        selectionRectangle.render();
        
        DrawFPS(10, 10);
        DrawText(TextFormat("Grid size: x: %.02f, y: %.02f", gridSize.x, gridSize.y), 10, 30, 10, LIME);
        DrawText(TextFormat("Selected square: (%.02f, %.02f), (%.02f, %.02f)", selRectPos.x + 0.5f, selRectPos.y + 0.5f, selRectPos.x - 0.5f, selRectPos.y - 0.5f), 10, 40, 10, LIME);
        
        EndDrawing();
        /* End Drawing */

        // Update framecount
        frameCount++;
    }
    CloseWindow();
    return 0;
}