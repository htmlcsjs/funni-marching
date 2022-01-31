#include <raylib.h>

#pragma once

namespace helpers2D
{
    class Dot
    {
    private:
        Vector2 gridPos;
        Vector2 realPos;
        Color colour;
        float unitSize;
    public:
        Dot(Vector2 gridPos, Color colour, float unitSize);
        Dot(int x, int y, Color colour, float unitSize);
        ~Dot();

        void render();
        void setColour(Color colour);
        void setGridPos(Vector2 pos);
        Vector2 getGridPos();
        void updateUnitSize(float unitSize);
    };
} // namespace helpers2D