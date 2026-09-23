#include "Rigidbody.h"

Rigidbody::Rigidbody(std::vector<float> initialPositionWorld)
    : massTons(1.0f),
      positionWorld(std::move(initialPositionWorld)),
      velocity{0.0f, 0.0f},
      acceleration{0.0f, 0.0f}
{
}

void Rigidbody::updatePosition(float deltaTime)
{
	// Update position based on velocity and deltaTime
	positionWorld[0] += velocity[0] * deltaTime;
	positionWorld[1] += velocity[1] * deltaTime;
}

void Rigidbody::updateVelocity(float deltaTime)
{
	// Update velocity based on acceleration and deltaTime
	velocity[0] += acceleration[0] * deltaTime;
	velocity[1] += acceleration[1] * deltaTime;
}

void Rigidbody::applyForce(float forceX, float forceY)
{
	// Calculate acceleration based on force and mass
	acceleration[0] = forceX / massTons;
	acceleration[1] = forceY / massTons;
	std::cout << "Applied force" << std::endl;
	std::cout << "position: (" << positionWorld[0] << ", " << positionWorld[1] << ")" << std::endl;
}

void Rigidbody::update(float deltaTime)
{
	updateVelocity(deltaTime);
	updatePosition(deltaTime);
}

std::vector<float> Rigidbody::getPosition() const
{
	return positionWorld;
}