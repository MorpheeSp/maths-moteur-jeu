#include "Controller.h"
#include <QKeyEvent>

void Controller::handleInput()
{
	// Handle input for selected rigidbodies based on the current state of the controller
	for (auto& rb : selectedRigidbodies)
	{
		rb->applyForce(right * base_acceleration - left * base_acceleration, down * base_acceleration - up * base_acceleration);
	}
}