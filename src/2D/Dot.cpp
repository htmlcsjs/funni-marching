#include <raylib.h>
#include "Dot.hpp"

using namespace helpers2D;

Dot::Dot(Vector2 gridPos, Color colour, float unitSize)
{
    this->gridPos = gridPos;
    this->colour = colour;
    this->unitSize = unitSize;
    this->setGridPos(gridPos);
}

Dot::Dot(int x, int y, Color colour, float unitSize) 
{
    this->gridPos = (Vector2){x, y};
    this->colour = colour;
    this->unitSize = unitSize;
    this->setGridPos((Vector2){x, y});
}

Dot::~Dot() 
{
    
}

void Dot::render() 
{
    DrawCircleV(realPos, 2, colour);
}

void Dot::setColour(Color colour) 
{
    this->colour = colour;
}

void Dot::setGridPos(Vector2 pos) 
{
    int halfScreenX = GetScreenWidth() / 2;
    int halfScreenY = GetScreenHeight() / 2;

    this->gridPos = pos;
    this->realPos.x = (pos.x) * unitSize + halfScreenX;
    this->realPos.y = (pos.y * -1) * unitSize + halfScreenY;
}

Vector2 Dot::getGridPos() 
{
    return gridPos;
}

void Dot::updateUnitSize(float unitSize) 
{
    this->unitSize = unitSize;
    this->setGridPos(this->gridPos);
}
