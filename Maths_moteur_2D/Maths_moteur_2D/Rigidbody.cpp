#include "Rigidbody.h"

Rigidbody::Rigidbody(std::vector<float> initialPositionWorld)
    : massTons(1.0f),
      positionWorld(std::move(initialPositionWorld)),
      velocity{0.0f, 0.0f},
      acceleration{0.0f, 0.0f},
	  instantAcceleration{ 0.0f, 0.0f }
{
}

// Fonctions privées pour mettre à jour la position et la vitesse du rigidbody en fonction de l'accélération et du temps écoulé
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

// Fonction publique, appellée pour appliquer une force sur le rigidbody, modifiant ainsi son accélération
void Rigidbody::applyForce(float forceX, float forceY)
{
	// Calculate acceleration based on force and mass
	instantAcceleration[0] += forceX / massTons;
	instantAcceleration[1] += forceY / massTons;
}

// Fonction publique, appelée pour mettre à jour l'état du rigidbody en fonction du temps écoulé
void Rigidbody::update(float deltaTime)
{

	// Apply drag force based on current velocity
	instantAcceleration[0] -= drag * velocity[0];
	instantAcceleration[1] -= drag * velocity[1];

	// A la fin, on met à jour l'accélération, la vitesse et la position du rigidbody
	acceleration = instantAcceleration;

	// Update velocity and position based on the current acceleration
	updateVelocity(deltaTime);
	updatePosition(deltaTime);

	// Reset instant acceleration to zero after calculating
	instantAcceleration[0] = 0.0f;
	instantAcceleration[1] = 0.0f;
}