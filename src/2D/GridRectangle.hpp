#include <raylib.h>

#pragma once

namespace helpers2D
{
    class GridRectangle
    {
    private:
        Rectangle rectangle;
        Vector2 gridPos;
        Color colour;
        float unitSize;
    public:
        GridRectangle(Vector2 gridPos, Vector2 size, Color colour, float unitSize);
        GridRectangle(float posX, float posY, float sizeX, float sizeY, Color colour, float unitSize);
        ~GridRectangle();

        void render();
        void setColour(Color colour);
        void setGridPos(Vector2 pos);
        Vector2 getGridPos();
    };
 } // namespace helpers2D