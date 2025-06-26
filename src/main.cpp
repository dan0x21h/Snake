#include <QApplication>
#include "gamepanel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GamePanel game;
    game.show();
    return app.exec();
}
