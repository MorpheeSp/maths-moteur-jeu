#include <GameWindow.h>
#include <QKeyEvent>
#include <QPainter>
#include <utility>

#include "Entity.h"

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


// Constructeur initialisé ci-dessous

GameWindow::GameWindow(QWidget* parent) : QMainWindow(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    // Initialise le timer de mise à jour (20 ms)

	// Create a rigidbody and select it for control
	Rigidbody* rb = new Rigidbody({ 0.0f, 0.0f }, "../../ressources/images/custom_space_ship.png");
	controller.selectRigidbody(rb);

	// Create two planets to test the gravitational attraction
	Rigidbody* planet1 = new Rigidbody({ 100.0f, 0.0f });
	planet1->setCelestialGravity(1000);  // Set a large mass for the planet
	Rigidbody* planet2 = new Rigidbody({ -100.0f, 0.0f });
	planet2->setCelestialGravity(1000);  // Set a large mass for the planet

	// Create one entity that follows the player around
	Entity* enemy = new Entity({150.0f, 150.0f}, rb);

	// Définition des limites du terrain
	QSize WSize = this->size();
	// Limites en coordonnées d'écran
	bounds.push_back(std::vector<int>{WSize.width() / 10, WSize.height() / 10});
	bounds.push_back(std::vector<int>{WSize.width(), WSize.height()});

	// Limites en coordonnées physiques
	WorldPoint lowerBound = WorldPoint{ screentoWorld(ScreenPoint{double(bounds[0][0]), double(bounds[0][1])}, WSize.width(), WSize.height(), 1)};
	worldBounds.push_back(std::vector<float>{float(lowerBound.first), float(lowerBound.second)});
	WorldPoint higherBound = WorldPoint{ screentoWorld(ScreenPoint{double(bounds[1][0]), double(bounds[1][1])}, WSize.width(), WSize.height(), 1)};
	worldBounds.push_back(std::vector<float>{float(higherBound.first), float(higherBound.second)});


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
	for (Rigidbody* rb : Rigidbody::getRigidbodies())
	{
		// Mise à jour des positions
		rb->update(0.02f);
	}

	for (Entity* ent : Entity::getAllEntities()) {
		ent->followTarget();
	}

	// Tester si les rigidbodies sortent de la zone délimitée
	for (Rigidbody* rb : Rigidbody::getRigidbodies()) {
		ScreenPoint pos_screen = worldToScreen(ScreenPoint{ rb->getPosition()[0], rb->getPosition()[1] }, this->size().width(), this->size().height(), 1);  // position du rb sur l'écran
		if (pos_screen.first < bounds[0][0]) {  // Si le rb dépasse à la limite gauche de l'écran
			// Placer le rb à la position limite + 1 (légèrement plus à l'intérieur)
			rb->setVelocity({ -rb->getVelocity()[0] , rb->getVelocity()[1] });
		}
		else if (pos_screen.first > bounds[1][0]) {  // Si le rb dépasse à la limite droite de l'écran
			// Placer le rb à la position limite - 1 (légèrement plus à l'intérieur)
			rb->setVelocity({ -rb->getVelocity()[0] , rb->getVelocity()[1] });
		}
		if (pos_screen.second < bounds[0][1]) {  // Si le rb dépasse à la limite haute de l'écran
			// Placer le rb à la position limite + 1 (légèrement plus à l'intérieur)
			rb->setVelocity({ rb->getVelocity()[0] , -rb->getVelocity()[1] });
		}
		else if (pos_screen.second > bounds[1][1]) {  // Si le rb dépasse à la limite basse de l'écran
			// Placer le rb à la position limite + 1 (légèrement plus à l'intérieur)
			rb->setVelocity({ rb->getVelocity()[0] , -rb->getVelocity()[1] });
		}
	}


    update();
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
    ScreenPoint screenMiddlePoint = worldToScreen(worldOrigin, this->size().width(), this->size().height(), 1);
    painter.drawEllipse(screenMiddlePoint.first, screenMiddlePoint.second, radius, radius);

	// Draw the positions of all rigidbodies as green circles.
	painter.setBrush(Qt::green);
	painter.setPen(Qt::NoPen);
	for (Rigidbody* rb : Rigidbody::getRigidbodies()) {
		std::vector<float> positionWorld = rb->getPosition();
		WorldPoint worldPos = { positionWorld[0], positionWorld[1] };
		ScreenPoint screenPos = worldToScreen(worldPos, this->size().width(), this->size().height(), 1);
		painter.drawEllipse(screenPos.first, screenPos.second, radius, radius);
	}

	// Draw the position of the selected rigidbodies as a blue circle.
	painter.setBrush(Qt::blue);
	painter.setPen(Qt::NoPen);
	if (!controller.selectedRigidbodies.empty()) {
		for (Rigidbody* rb : controller.selectedRigidbodies) {
			std::vector<float> positionWorld = rb->getPosition();
			WorldPoint worldPos = { positionWorld[0], positionWorld[1] };
			ScreenPoint screenPos = worldToScreen(worldPos, this->size().width(), this->size().height(), 1);
			painter.drawEllipse(screenPos.first, screenPos.second, radius, radius);

			// transformations de l'image du vaisseau
			QTransform transform;
			transform.translate(screenPos.first, screenPos.second);
			transform.rotate(rb->getRotationAngle());  // Rotate based on the vector

			painter.setTransform(transform);
			painter.drawPixmap(
				-rb->getImageSize().width() / 2,
				-rb->getImageSize().height() / 4,
				rb->getImage().scaled(rb->getImageSize(), Qt::KeepAspectRatio)
			);
			painter.resetTransform();
		}
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