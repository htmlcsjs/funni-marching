#include <raylib.h>
#include "Line.hpp"

using namespace helpers2D;

Line::Line(Vector2 startPos, Vector2 endPos, Color colour)
{
    this->startPos = startPos;
    this->endPos = endPos;
    this->colour = colour;
}

Line::Line(int startX, int startY, int endX, int endY, Color colour)
{
    this->startPos = {(float) startX, (float) startY};
    this->endPos = {(float) endX, (float) endY};
    this->colour = colour;
}

Line::~Line()
{
}

void Line::render() 
{
    DrawLineV(startPos, endPos, colour);
}

void Line::changeColour(Color colour) 
{
    this->colour = colour;
}
