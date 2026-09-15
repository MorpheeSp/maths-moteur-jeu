
#include "rigidbody.h"

void rigidbody::updatePosition(float deltaTime)
{
	// Update position based on velocity and deltaTime
	positionWorld[0] += velocity[0] * deltaTime;
	positionWorld[1] += velocity[1] * deltaTime;
}

void rigidbody::updateVelocity(float deltaTime)
{
	// Update velocity based on acceleration and deltaTime
	velocity[0] += acceleration[0] * deltaTime;
	velocity[1] += acceleration[1] * deltaTime;
}

void rigidbody::update(float deltaTime)
{
	updateVelocity(deltaTime);
	updatePosition(deltaTime);
}

void rigidbody::applyForce(float forceX, float forceY)
{
	// Calculate acceleration based on force and mass
	acceleration[0] = forceX / massTons;
	acceleration[1] = forceY / massTons;
}