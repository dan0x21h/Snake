#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QFont>
#include <QPen>
#include <qsize.h>

static const long INTERVALL = 100;
static const long SLOW_INTERVALL = 2 * INTERVALL;
static const QSize WINDOW_SIZE = QSize(600, 400);
static const int ESIZE = 20;

static const QPen RED_PEN = QPen(Qt::red, 0);
static const QPen GREEN_PEN = QPen(Qt::darkGreen, 0);
static const QPen WHITE_PEN = QPen(Qt::white, 0);
static const QPen YELLOW_PEN = QPen(Qt::darkYellow, 3);

static const QBrush RED_BRUSH = QBrush(Qt::red);
static const QBrush GREEN_BRUSH = QBrush(Qt::darkGreen);

static const QFont BIG_FONT = QFont("Times", 25, QFont::Bold);

static const int _u = Qt::Key_Up;
static const int _d = Qt::Key_Down;
static const int _l = Qt::Key_Left;
static const int _r = Qt::Key_Right;
static const int _border = Qt::Key_D;
static const int _cross = Qt::Key_C;
static const int _death = Qt::Key_N;

#endif // CONSTANTS_H
