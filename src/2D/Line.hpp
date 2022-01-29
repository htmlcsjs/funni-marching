#include <raylib.h>

#pragma once

namespace helpers2D
{
    class Line
    {
    private:
        Vector2 startPos;
        Vector2 endPos;
        Color colour;
    public:
        Line(Vector2 startPos, Vector2 endPos, Color colour);
        Line(int startX, int startY, int endX, int endY, Color colour);
        ~Line();

        void render();
        void changeColour(Color colour);
    };
 } // namespace helpers2D