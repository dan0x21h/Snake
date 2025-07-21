#include <QApplication>
#include "gamepanel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/snake_icon.png"));
    GamePanel game;
    game.show();
    return app.exec();
}
