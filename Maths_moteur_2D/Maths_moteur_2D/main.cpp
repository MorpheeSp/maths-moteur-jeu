#include "Mm2D.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Mm2D window;
    window.show();
    return app.exec();
}
