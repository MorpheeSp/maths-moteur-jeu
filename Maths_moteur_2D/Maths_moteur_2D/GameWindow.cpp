#include <GameWindow.h>
#include <QKeyEvent>
#include <QPainter>
#include <utility>


// Constructeur initialisé ci-dessous

GameWindow::GameWindow(QWidget* parent) : QMainWindow(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    // Initialise le timer de mise à jour (20 ms)

	// Create a rigidbody and select it for control
	Rigidbody* rb = new Rigidbody({ 0.0f, 0.0f });
	controller.selectRigidbody(rb);

	// Create two planets to test the gravitational attraction
	Rigidbody* planet1 = new Rigidbody({ 100.0f, 0.0f });
	planet1->setCelestialGravity(1000);  // Set a large mass for the planet
	Rigidbody* planet2 = new Rigidbody({ -100.0f, 0.0f });
	planet2->setCelestialGravity(1000);  // Set a large mass for the planet

    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    timer->start(20);
}

GameWindow::~GameWindow()
{
}

void GameWindow::updateGame()
{
    // Appel du controller pour gérer l'entrée et mise à jour de l'affichage
    controller.handleInput();

	// Mettre à jour tous les rigidbodies
	for (Rigidbody* rb : Rigidbody::getRigidbodies()) {rb->update(0.02f);}
    update();
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

    // Draw screen center as a red circle.
    int radius = 10;
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
    WorldPoint worldOrigin = { 0,0 };
    ScreenPoint screenMiddlePoint = worldToScreen(worldOrigin, 800, 600, 1);
    painter.drawEllipse(screenMiddlePoint.first, screenMiddlePoint.second, radius, radius);

	// Draw the positions of all rigidbodies as green circles.
	painter.setBrush(Qt::green);
	painter.setPen(Qt::NoPen);
	for (Rigidbody* rb : Rigidbody::getRigidbodies()) {
		std::vector<float> positionWorld = rb->getPosition();
		WorldPoint worldPos = { positionWorld[0], positionWorld[1] };
		ScreenPoint screenPos = worldToScreen(worldPos, 800, 600, 1);
		painter.drawEllipse(screenPos.first, screenPos.second, radius, radius);
	}

	// Draw the position of the selected rigidbody as a blue circle.
	painter.setBrush(Qt::blue);
	painter.setPen(Qt::NoPen);
	if (!controller.selectedRigidbodies.empty()) {
		Rigidbody* rb = controller.selectedRigidbodies[0];
		std::vector<float> positionWorld = rb->getPosition();
		WorldPoint worldPos = { positionWorld[0], positionWorld[1] };
		ScreenPoint screenPos = worldToScreen(worldPos, 800, 600, 1);
		painter.drawEllipse(screenPos.first, screenPos.second, radius, radius);
	}
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        // Left key pressed.
		if (controller.right) {
			controller.right = false; // Stop moving right if the right key was previously pressed
		}
		controller.left = true;
        break;

    case Qt::Key_Right:
		if (controller.left) {
			controller.left = false; // Stop moving left if the left key was previously pressed
		}
		controller.right = true;
        break;

    case Qt::Key_Up:
		if (controller.down) {
			controller.down = false; // Stop moving down if the down key was previously pressed
		}
		controller.up = true;
        break;

    case Qt::Key_Down:
		if (controller.up) {
			controller.up = false; // Stop moving up if the up key was previously pressed
		}
		controller.down = true;
        break;

    case Qt::Key_Space:
        controller.stop = true;
		controller.up = false;
		controller.down = false;
		controller.left = false;
		controller.right = false;
        break;

    default:
        QWidget::keyPressEvent(event);
        return;
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_Left:
		controller.left = false;
		break;
	case Qt::Key_Right:
		controller.right = false;
		break;
	case Qt::Key_Up:
		controller.up = false;
		break;
	case Qt::Key_Down:
		controller.down = false;
		break;
	case Qt::Key_Space:
		controller.stop = false;
		break;
	default:
		QWidget::keyReleaseEvent(event);
		return;
	}
}