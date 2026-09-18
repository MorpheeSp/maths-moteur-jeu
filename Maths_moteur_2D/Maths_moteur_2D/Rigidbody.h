#include <vector>

class Rigidbody
{
	int massTons;
	std::vector<float> positionWorld;
	std::vector<float> velocity;
	std::vector<float> acceleration;

	void updatePosition(float);  // Calcule un changement de position selon la vitesse et le temps écoulé
	void updateVelocity(float);  // Calcule un changement de vitesse selon l'accélération et le temps écoulé
public:
	void applyForce(float forceX, float forceY);  // Modifier l'accélération selon la force appliquée et la masse
	void update(float);  // Met à jour la position et la vitesse selon l'accélération et le temps écoulé
};
