#pragma once

#include "snakewidget.h"
#include <QWidget>

class GamePanel : public QWidget
{
  Q_OBJECT

public:
  GamePanel();

protected:
  void keyPressEvent(QKeyEvent *event);

private slots:
  void update();

private:
  void handlePause();
  void handleSpeed();

private:
  std::unique_ptr<SnakeWidget> snakeWidget;
  std::shared_ptr<QTimer> timer;
};