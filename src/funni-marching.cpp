#include <algorithm>
#include <charconv>
#include <iostream>
#include <map>
#include <raylib.h>
#include <vector>

#include "2D/Dot.hpp"
#include "2D/Line.hpp"
#include "2D/GridRectangle.hpp"
#include "2D/RenderingFunctions.hpp"

// Const and Var declaration
const int fps = 150;
const int scrollSpeed = 4;
const Color gridColour = DARKBLUE;

std::vector<helpers2D::Line> gridlines;
std::vector<helpers2D::Dot> gridDots;
std::vector<Vector2> gridDotsPos; // TODO move to std::set
Vector2 gridSize;
unsigned int unitSize = 100;

// Resources
extern const unsigned char _binary_resources_logo_png_start, _binary_resources_logo_png_end;
size_t logo_png_size = &_binary_resources_logo_png_end - &_binary_resources_logo_png_start;

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}


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

    Vector2 oldSelRectPos;
    bool manualMove = true;
    
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
        if (keyDownDown && frameCount % selRectSpeed == 0 && manualMove)
        {
            selRectPos.y -= 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }
        else if (keyDownUp && frameCount % selRectSpeed == 0 && manualMove)
        {
            selRectPos.y += 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }
        if (keyDownLeft && frameCount % selRectSpeed == 0 && manualMove)
        {
            selRectPos.x -= 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }
        else if (keyDownRight && frameCount % selRectSpeed == 0 && manualMove)
        {
            selRectPos.x += 1.0f;
            selectionRectangle.setGridPos(selRectPos);
        }

        // automatic sel rect moving
        if (!manualMove) {
            if (selRectPos.y < gridSize.y * -1.0) 
            {
                Vector2 funniPos = selRectPos;
                funniPos.y = gridSize.y + 0.5f;
                funniPos.x += 1.0f;
                selectionRectangle.setGridPos(funniPos);
            }
            else if (selRectPos.x > gridSize.x + 1) 
            {
                manualMove = true;
            }
            else
            {
                selRectPos.y -= 1.0f;
                selectionRectangle.setGridPos(selRectPos);
            }
        }

        // some auto move based keybinds
        if (IsKeyDown(KEY_M) && frameCount % selRectSpeed == 0) 
        {
            manualMove = !manualMove;
        }
        if (IsKeyDown(KEY_C))
        {
            gridDots.clear();
            gridDotsPos.clear();
        }
        if (IsKeyDown(KEY_R))
        {
            gridDots.clear();
            gridDotsPos.clear();
            selRectPos = (Vector2){gridSize.x * -1 - 0.5, gridSize.y + 0.5};
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
            for (auto & dot : gridDots)
            {
                dot.updateUnitSize(unitSize);
            }
        }
        
        // regen grid if window is resized
        if (IsWindowResized())
        {
            gridSize = (Vector2){0,0};
            gridlines.clear();
            generateGrid();
            selectionRectangle.setGridPos(selRectPos);
            for (auto & dot : gridDots)
            {
                dot.setGridPos(dot.getGridPos());
            }
        }
        
        // add dots at sel rect pos
        if (!(selRectPos == oldSelRectPos)) {
            Vector2 TLPos = (Vector2){selRectPos.x - 0.5f, selRectPos.y + 0.5f};
            Vector2 TRPos = (Vector2){selRectPos.x + 0.5f, selRectPos.y + 0.5f};
            Vector2 BLPos = (Vector2){selRectPos.x - 0.5f, selRectPos.y - 0.5f};
            Vector2 BRPos = (Vector2){selRectPos.x + 0.5f, selRectPos.y - 0.5f};
            if (std::find(gridDotsPos.begin(), gridDotsPos.end(), TLPos) == gridDotsPos.end())
            {
                float val = helpers2D::RenderingFunctions::circle(TLPos.x, TLPos.y, 10.0f);
                if (val <= 1) 
                {
                    gridDots.push_back(helpers2D::Dot(TLPos, GREEN, unitSize));
                    gridDotsPos.push_back(TLPos);
                }
                else 
                {
                    gridDots.push_back(helpers2D::Dot(TLPos, GetColor(0x00f2f2), unitSize));
                    gridDotsPos.push_back(TLPos);
                }
            }
            if (std::find(gridDotsPos.begin(), gridDotsPos.end(), TRPos) == gridDotsPos.end())
            {
                float val = helpers2D::RenderingFunctions::circle(TRPos.x, TRPos.y, 10.0f);
                if (val <= 1) 
                {
                    gridDots.push_back(helpers2D::Dot(TRPos, GREEN, unitSize));
                    gridDotsPos.push_back(TRPos);
                }
                else 
                {
                    gridDots.push_back(helpers2D::Dot(TRPos, GetColor(0x00f2f2), unitSize));
                    gridDotsPos.push_back(TRPos);
                }
            }
            if (std::find(gridDotsPos.begin(), gridDotsPos.end(), BLPos) == gridDotsPos.end())
            {
                float val = helpers2D::RenderingFunctions::circle(BLPos.x, BLPos.y, 10.0f);
                if (val <= 1) 
                {
                    gridDots.push_back(helpers2D::Dot(BLPos, GREEN, unitSize));
                    gridDotsPos.push_back(BLPos);
                }
                else 
                {
                    gridDots.push_back(helpers2D::Dot(BLPos, GetColor(0x00f2f2), unitSize));
                    gridDotsPos.push_back(BLPos);
                }
            }
            if (std::find(gridDotsPos.begin(), gridDotsPos.end(), BRPos) == gridDotsPos.end())
            {
                float val = helpers2D::RenderingFunctions::circle(BRPos.x, BRPos.y, 10.0f);
                if (val <= 1) 
                {
                    gridDots.push_back(helpers2D::Dot(BRPos, GREEN, unitSize));
                    gridDotsPos.push_back(BRPos);
                }
                else 
                {
                    gridDots.push_back(helpers2D::Dot(BRPos, GetColor(0x00f2f2), unitSize));
                    gridDotsPos.push_back(BRPos);
                }
            }
        }

        /* Drawing */
        BeginDrawing();

        ClearBackground(GetColor(0x060600));
        
        for (auto& line : gridlines)
        {
            line.render();
        }
        selectionRectangle.render();
        for (auto & dot : gridDots)
        {
            dot.render();
        }
        
        DrawFPS(10, 10);
        DrawText(TextFormat("Grid size: x: %.02f, y: %.02f", gridSize.x, gridSize.y), 10, 30, 10, LIME);
        DrawText(TextFormat("Selected square: (%.02f, %.02f), (%.02f, %.02f)", selRectPos.x + 0.5f, selRectPos.y + 0.5f, selRectPos.x - 0.5f, selRectPos.y - 0.5f), 10, 40, 10, LIME);
        
        // Update framecount
        frameCount++;
        oldSelRectPos = selRectPos;
        EndDrawing();
        /* End Drawing */
    }
    CloseWindow();
    return 0;
}