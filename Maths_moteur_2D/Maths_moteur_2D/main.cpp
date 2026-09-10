#include "Maths_moteur_2D.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Maths_moteur_2D window;
    window.show();
    return app.exec();
}
