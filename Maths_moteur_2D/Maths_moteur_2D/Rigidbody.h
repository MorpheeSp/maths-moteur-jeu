#include <vector>

class rigidbody
{
	int massTons;
	std::vector<float> positionWorld;
	std::vector<float> velocity;
	std::vector<float> acceleration;

	void updatePosition(float);
	void updateVelocity(float);
	void update(float);
public:
	void applyForce(float forceX, float forceY);
};
