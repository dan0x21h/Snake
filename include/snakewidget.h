#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QGridLayout>
#include <QPaintEvent>
#include <QString>
#include <QWidget>
#include <deque>
#include <snakeelement.h>

using direction = std::pair<int, int>;

class SnakeWidget : public QWidget
{
  Q_OBJECT

public:
  SnakeWidget(QWidget *parent);
  void move();
  std::pair<int, int> calculateNextPosition();
  void generateFood();
  void checkIfEat();
  void checkCollision();
  void setCommand(const int key);
  void start();
  void reset();

protected:
  void paintEvent(QPaintEvent *event);

private:
  void drawStartScreen(QPainter &painter);
  void drawGameOver(QPainter &painter);
  void drawFood(QPainter &painter);
  void drawSnake(QPainter &painter);
  void drawPointsAndInfo(QPainter &painter);
  void drawLostAnimation(QPainter &painter);
  bool isOnBorder(SnakeElement &food);

private:
  direction snake_direction;
  std::map<int, direction> directions;
  std::deque<SnakeElement> snake_items;
  SnakeElement food;
  bool isStarted;
  bool hasFood;
  bool justAte;
  bool isGameOver;
  bool isLostAnimationStarted;
  bool borderPlacementAllowed;
  bool nodeath;
  bool allowCrossingSnake;
  int score;
  int animationCounter;
  int MAX_SNAKE_LENGTH;
};

#endif // SNAKEWIDGET_H
