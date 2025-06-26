#include "gamepanel.h"
#include "snakewidget.h"
#include <QtGui>

GamePanel::GamePanel() : QWidget() {
    snakeWidget = std::make_unique<SnakeWidget>(this);
    auto layout = std::make_unique<QGridLayout>();
    layout->addWidget(snakeWidget.get(), 0, 0);
    setLayout(layout.get());

    timer = std::make_shared<QTimer>(this);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(update()));
    timer->start(INTERVALL);

    setFixedSize(WINDOW_SIZE);
    setWindowTitle(tr("Snake"));
}

void GamePanel::keyPressEvent(QKeyEvent *event) {
    auto key = event->key();
    switch(key) {
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
    case Qt::Key_F:
        handleSpeed();
        break;
    default:
        snakeWidget->setCommand(key);
    }
}

void GamePanel::update() {
    snakeWidget->checkIfEat();
    snakeWidget->generateFood();
    snakeWidget->move();
    snakeWidget->checkCollision();
    snakeWidget->repaint();
}

void GamePanel::handlePause() {
    if(timer->isActive()) {
        timer->stop();
    } else {
        timer->start(INTERVALL);
    }
}

void GamePanel::handleSpeed()
{
    timer->setInterval(timer->intervalAsDuration()
                       .count() == INTERVALL ? SLOW_INTERVALL : INTERVALL);
}
