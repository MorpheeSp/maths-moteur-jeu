#include "Entity.h"


Entity::Entity(std::vector<float> initialPositionWorld) : Rigidbody(initialPositionWorld) {
	setCelestialGravity(0);
	totalMaxAcc = 100;  // Par défaut
	allEntities.push_back(this);
}

Entity::Entity(std::vector<float> initialPositionWorld, Rigidbody* targetBody) : Rigidbody(initialPositionWorld) {
	setCelestialGravity(0);
	setTarget(targetBody);
	totalMaxAcc = 100;  // par défaut
	allEntities.push_back(this);
}

void Entity::followTarget() {
	float dX = target->getPosition()[0] - getPosition()[0];
	float dY = target->getPosition()[1] - getPosition()[1];
	float distance = std::sqrt(dX * dX) + std::sqrt(dY * dY);
	applyForce(dX / distance * totalMaxAcc, dY / distance * totalMaxAcc);
}