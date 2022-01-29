#include <raylib.h>
#include "GridRectangle.hpp"

using namespace helpers2D;

GridRectangle::GridRectangle(Vector2 gridPos, Vector2 size, Color colour, float unitSize) 
{
    this->colour = colour;
    this->unitSize = unitSize;
    this->rectangle.height = size.y * unitSize + 1;
    this->rectangle.width = size.x * unitSize + 1;
    this->setGridPos(gridPos);
}

GridRectangle::GridRectangle(float posX, float posY, float sizeX, float sizeY, Color colour, float unitSize) 
{
    this->colour = colour;
    this->unitSize = unitSize;
    this->rectangle.height = sizeY * unitSize + 1;
    this->rectangle.width = sizeX * unitSize + 1;
    this->setGridPos((Vector2){posX, posY});
}

GridRectangle::~GridRectangle() 
{
    
}

void GridRectangle::render() 
{
    DrawRectangleLinesEx(this->rectangle, 1, this->colour);
}

void GridRectangle::setColour(Color colour) 
{
    this->colour = colour;
}

void GridRectangle::setGridPos(Vector2 pos) 
{
    int halfScreenX = GetScreenWidth() / 2;
    int halfScreenY = GetScreenHeight() / 2;

    this->gridPos = pos;
    this->rectangle.x = (pos.x - .5) * unitSize + halfScreenX;
    this->rectangle.y = (pos.y * -1 - .5) * unitSize + halfScreenY;
}

Vector2 GridRectangle::getGridPos() 
{
    return gridPos;
}