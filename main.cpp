#include <QApplication>
#include <QtWidgets>
#include "game.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Game fenetre;
    fenetre.show();
    return app.exec();
}
