#include <vector>
#include <iostream>

class Rigidbody
{
	// Tableau contenant tous les Rigidbody créés dans le jeu
	inline static std::vector<Rigidbody*> rigidbodies;

	float drag = 0.1f;  // Coefficient de traînée pour simuler la résistance de l'air ou d'autres forces de frottement
	int massTons;  // Masse du rigidbody en tonnes

	float celestialGravity = 0;  // Gravité qui sera appliquée à tous les rigidbody.

	// Vecteurs relatifs aux mouvements effectifs
	std::vector<float> positionWorld;
	std::vector<float> velocity;
	std::vector<float> acceleration;

	// Accélération en cours de calcul
	std::vector<float> instantAcceleration;


	// Méthodes privées pour mettre à jour les position, vitesse et accélération du rigidbody
	void updatePosition(float);  // Calcule un changement de position selon la vitesse et le temps écoulé
	void updateVelocity(float);  // Calcule un changement de vitesse selon l'accélération et le temps écoulé

public:
	void applyForce(float forceX, float forceY);  // Modifier l'accélération selon la force appliquée et la masse
	void update(float);  // Met à jour la position et la vitesse selon l'accélération et le temps écoulé
	Rigidbody(std::vector<float> initialPositionWorld);  // Constructeur qui initialise la masse et la position du rigidbody

	// Fonctions statiques
	std::vector<float> gravityFromPosition(const std::vector<float>& position, float massTonsTarget) const;  // Calcule la gravité appliquée à un rigidbody selon sa position et sa masse
	static std::vector<Rigidbody*> getRigidbodies(){ return rigidbodies; }  // Retourne la liste de tous les rigidbodies

	// Getters et setters
	void setMass(int mass) { massTons = mass; }  // Définit la masse du rigidbody
	int getMass() const { return massTons; }  // Retourne la masse du rigidbody

	void setCelestialGravity(float gravity) { celestialGravity = gravity; }  // Définit la gravité appliquée à tous les rigidbody
	float getCelestialGravity() const { return celestialGravity; }  // Retourne la gravité appliquée à tous les rigidbody

	void setDrag(float dragCoefficient) { drag = dragCoefficient; }  // Définit le coefficient de traînée
	float getDrag() const { return drag; }  // Retourne le coefficient de traînée

	std::vector<float> getPosition() const { return positionWorld; }  // Retourne la position du rigidbody
	std::vector<float> getAcceleration() const { return acceleration; }  // Retourne l'accélération du rigidbody
};
