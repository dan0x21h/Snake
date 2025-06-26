#include "snakewidget.h"
#include <QtGui>

int rand(int border)
{
    int num;
    while (true)
    {
        num = QRandomGenerator::global()->generate() % border;
        if (num % ESIZE == 0)
            break;
    }
    return num;
}

SnakeWidget::SnakeWidget(QWidget *parent) : QWidget(parent), isStarted(false)
{
    setFixedSize(WINDOW_SIZE);
    directions[_u] = std::make_pair(0, -ESIZE);
    directions[_d] = std::make_pair(0, ESIZE);
    directions[_r] = std::make_pair(ESIZE, 0);
    directions[_l] = std::make_pair(-ESIZE, 0);
    reset();
}

void SnakeWidget::move()
{
    if (!isStarted || isLostAnimationStarted)
    {
        return;
    }
    auto nextPosition = calculateNextPosition();
    SnakeElement newRect(nextPosition.first, nextPosition.second);
    snake_items.push_front(newRect);

    if (justAte)
    {
        justAte = false;
    }
    else
    {
        snake_items.pop_back();
    }
}

std::pair<int, int> SnakeWidget::calculateNextPosition()
{
    auto first = snake_items.front();
    auto x = first.x + snake_direction.first;
    auto y = first.y + snake_direction.second;

    if (nodeath)
    {
        if (x < 0)
        {
            x = WINDOW_SIZE.width() - ESIZE;
        }
        else if (x > WINDOW_SIZE.width() - ESIZE)
        {
            x = 0;
        }

        if (y < 0)
        {
            y = WINDOW_SIZE.height() - ESIZE;
        }
        else if (y > WINDOW_SIZE.height() - ESIZE)
        {
            y = 0;
        }
    }

    return std::make_pair(x, y);
}

void SnakeWidget::generateFood()
{
    if (hasFood)
    {
        return;
    }

    while (true)
    {
        bool freePosition = true;
        int x = rand(WINDOW_SIZE.width());
        int y = rand(WINDOW_SIZE.height());

        food = SnakeElement(x, y);
        for (auto &item : snake_items)
        {
            if (item.getRect().intersects(food.getRect()))
            {
                freePosition = false;
            }
        }

        if (!borderPlacementAllowed && freePosition && isOnBorder(food))
        {
            freePosition = false;
        }

        if (freePosition)
            break;
    }
    hasFood = true;
}

void SnakeWidget::checkIfEat()
{
    if (food.getRect().intersects(snake_items.front().getRect()))
    {
        hasFood = false;
        justAte = true;
        score += 50;
    }
}

void SnakeWidget::checkCollision()
{
    if (nodeath)
        return;

    auto first = snake_items.front();
    if (first.x < 0 || (first.x + ESIZE) > WINDOW_SIZE.width() || first.y < 0 ||
        (first.y + ESIZE) > WINDOW_SIZE.height())
    {
        isLostAnimationStarted = true;
        return;
    }

    if (allowCrossingSnake)
        return;

    for (auto it = snake_items.begin() + 1; it != snake_items.end(); ++it)
    {
        if (it->getRect().intersects(first.getRect()))
        {
            isLostAnimationStarted = true;
            return;
        }
    }
}

void SnakeWidget::setCommand(const int key)
{
    if (((key == _u || key == _d) && !snake_direction.second) || ((key == _l || key == _r) && !snake_direction.first))
    {
        snake_direction = directions[key];
    }
    else if (key == _border)
    {
        borderPlacementAllowed = !borderPlacementAllowed;
    }
    else if (key == _cross)
    {
        allowCrossingSnake = !allowCrossingSnake;
    }
    else if (key == _death)
    {
        nodeath = !nodeath;
    }
}

void SnakeWidget::start() { isStarted = true; }

void SnakeWidget::reset()
{
    snake_items.clear();
    snake_direction = std::make_pair(-ESIZE, 0);
    hasFood = false;
    justAte = false;
    isGameOver = false;
    isLostAnimationStarted = false;
    borderPlacementAllowed = true;
    allowCrossingSnake = false;
    nodeath = false;
    score = 0;
    animationCounter = 0;
    int pos = 400;
    for (int x = 0; x < 10; ++x)
    {
        snake_items.push_back(SnakeElement(pos, 100));
        pos += ESIZE;
    }
}

void SnakeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!isStarted)
    {
        drawStartScreen(painter);
        return;
    }

    if (isGameOver)
    {
        drawGameOver(painter);
        return;
    }

    if (isLostAnimationStarted)
    {
        drawLostAnimation(painter);
        return;
    }

    drawFood(painter);
    drawSnake(painter);
    drawPointsAndInfo(painter);
}

void SnakeWidget::drawStartScreen(QPainter &painter)
{
    QString msg("SNAKE!\nThe famous Snake known from mobiles.\nPress S to start!");
    painter.setPen(WHITE_PEN);
    painter.setFont(BIG_FONT);
    painter.drawText(QRect(0, 0, WINDOW_SIZE.width(),
                           WINDOW_SIZE.height()),
                     Qt::AlignCenter, msg);
}

void SnakeWidget::drawGameOver(QPainter &painter)
{
    QString msg("Game Over!\nTotal Score: ");
    msg.append(QString::number(score))
        .append("\n\nPress R to restart or Q to quit!");
    painter.setPen(WHITE_PEN);
    painter.setFont(BIG_FONT);
    painter.drawText(QRect(0, 0, WINDOW_SIZE.width(),
                           WINDOW_SIZE.height()),
                     Qt::AlignCenter, msg);
}

void SnakeWidget::drawFood(QPainter &painter)
{
    if (!hasFood)
    {
        return;
    }
    painter.setPen(RED_PEN);
    painter.setBrush(RED_BRUSH);
    painter.drawRoundedRect(food.getRect(), 5, 5);
}

void SnakeWidget::drawSnake(QPainter &painter)
{
    painter.setPen(GREEN_PEN);
    painter.setBrush(GREEN_BRUSH);

    for (auto &item : snake_items)
    {
        painter.drawRoundedRect(item.getRect(), 5, 5);
    }
}

void SnakeWidget::drawPointsAndInfo(QPainter &painter)
{
    painter.setPen(WHITE_PEN);
    QString msg("Score: ");
    msg.append(QString::number(score));

    if (!borderPlacementAllowed)
    {
        msg.append(QString(" - no-border"));
    }

    if (allowCrossingSnake)
    {
        msg.append(QString(" - snake-crossing"));
    }

    if (nodeath)
    {
        msg.append(QString(" - no-death"));
    }

    painter.drawText(10, 15, msg);
}

void SnakeWidget::drawLostAnimation(QPainter &painter)
{
    auto color = ++animationCounter % 2 == 0 ? std::make_pair(GREEN_PEN, RED_BRUSH) : std::make_pair(RED_PEN, GREEN_BRUSH);
    painter.setPen(color.first);
    painter.setBrush(color.second);
    for (auto &item : snake_items)
    {
        painter.drawRoundedRect(item.getRect(), 5, 5);
    }

    if (animationCounter > 8)
    {
        isGameOver = true;
    }
}

bool SnakeWidget::isOnBorder(SnakeElement &food)
{
    return food.x == 0 ||
           food.y == 0 ||
           food.x == WINDOW_SIZE.width() - food.getRect().width() ||
           food.y == WINDOW_SIZE.height() - food.getRect().height();
}
