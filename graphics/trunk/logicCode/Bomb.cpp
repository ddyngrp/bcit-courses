#include "bombHeader.h"

Bomb::Bomb()
{
    bombSquare.x = 0;
    bombSquare.y = 0;;
}

void Bomb::explode()
{
    //isPlanted = 0;
}

void Bomb::setRect(int x, int y)
{
    bombSquare.x = x;
    bombSquare.y = y;
}
