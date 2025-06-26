#ifndef SNAKEELEMENT_H
#define SNAKEELEMENT_H

#include "constants.h"
#include <QRect>

struct SnakeElement
{
    int x, y;
    SnakeElement(int x, int y) : x(x), y(y) {}
    SnakeElement() : x(0), y(0) {}
    QRect getRect() const { return QRect(x, y, ESIZE, ESIZE); }
};

#endif // SNAKEELEMENT_H
