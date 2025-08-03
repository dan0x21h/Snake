#include "gamepanel.h"
#include "snakewidget.h"
#include <QtGui>

GamePanel::GamePanel() : QWidget(), currentInterval(INTERVALL)
{
    snakeWidget = std::make_unique<SnakeWidget>(this);
    auto layout = std::make_unique<QGridLayout>();
    layout->addWidget(snakeWidget.get(), 0, 0);
    setLayout(layout.get());

    timer = std::make_shared<QTimer>(this);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(update()));
    timer->start(currentInterval);

    setFixedSize(WINDOW_SIZE);
    setWindowTitle(tr("Snake"));
}

void GamePanel::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();
    switch (key)
    {
    case Qt::Key_Q:
        exit(EXIT_FAILURE);
        break;
    case Qt::Key_P:
        handlePause();
        break;
    case Qt::Key_R:
        snakeWidget->reset();
        break;
    case Qt::Key_S:
        snakeWidget->start();
        break;
    case Qt::Key_1:
        toggleSpeed();
        break;
    default:
        snakeWidget->setCommand(key);
    }
}

void GamePanel::update()
{
    snakeWidget->checkIfEat();
    snakeWidget->generateFood();
    snakeWidget->move();
    snakeWidget->checkCollision();
    snakeWidget->repaint();
}

void GamePanel::handlePause()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start(currentInterval);
    }
}

void GamePanel::toggleSpeed()
{
    switch (timer->intervalAsDuration().count())
    {
    case INTERVALL:
        timer->setInterval(MEDIUM_INTERVALL);
        break;
    case MEDIUM_INTERVALL:
        timer->setInterval(SLOW_INTERVALL);
        break;
    default:
        timer->setInterval(INTERVALL);
        break;
    }
}
