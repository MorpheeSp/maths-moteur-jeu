#include "Controller.h"
#include <QKeyEvent>

void Controller::handleInput()
{
	// Handle input for selected rigidbodies based on the current state of the controller
	for (auto& rb : selectedRigidbodies)
	{
		if (up) {
			rb->applyForce(0, -1); // Move up
		}
		if (down) {
			rb->applyForce(0, 1); // Move down
		}
		if (left) {
			rb->applyForce(-1, 0); // Move left
		}
		if (right) {
			rb->applyForce(1, 0); // Move right
		}
	}
}