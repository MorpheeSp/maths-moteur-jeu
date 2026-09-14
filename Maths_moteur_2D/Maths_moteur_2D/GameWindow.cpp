#include <GameWindow.h>
#include <QKeyEvent>
#include <QPainter>
#include <utility>

GameWindow::GameWindow(QWidget* parent) :
    QMainWindow(parent)
{
}

GameWindow::~GameWindow()
{
}




using ScreenPoint = std::pair<double, double>;
using WorldPoint = std::pair<double, double>;
//x -> world et X ->screen
ScreenPoint worldToScreen(const WorldPoint& worldPt, double W, double H, double z) {
    //x ->X
    double x = worldPt.first;
    double y = worldPt.second;

    double X = (x * z) + (W / 2);
    double Y = (y * z) + (H / 2);

    return ScreenPoint{ X, Y };
}

WorldPoint screentoWorld(const ScreenPoint& point, double W, double H, double z) {
    // X -> x
    double X = point.first;
    double Y = point.second;


    double x = (X - (W / 2)) / z;
    double y = (Y - (H / 2)) / z;

    return WorldPoint{ x, y };
}


void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Clear background with White color.
    painter.fillRect(rect(), Qt::white);

    // Draw player as a yellow circle.
    int radius = 10;

    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::NoPen);
    WorldPoint worldOrigin = { 0,0 };
    ScreenPoint screenMiddlePoint = worldToScreen(worldOrigin,800,600,1);
    painter.drawEllipse(screenMiddlePoint.first, screenMiddlePoint.second, radius, radius);
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        // Left key pressed.
        break;

    case Qt::Key_Right:
        // Right key pressed.
        break;

    case Qt::Key_Up:
        // Up key pressed.
        break;

    case Qt::Key_Down:
        // Down key pressed.
        break;

    default:
        QWidget::keyPressEvent(event);
        return;
    }
}
