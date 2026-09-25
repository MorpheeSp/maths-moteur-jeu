#pragma once
#include "Rigidbody.h"

// Classe qui sélectionne un ou plusieurs rigidbody et contrôle leur mouvement en fonction des entrées de l'utilisateur (clavier, souris, etc.)
class Controller
{
	float base_acceleration = 20.0f;

	public:
		// Flags pour garder en mémoire l'état des touches de direction
		bool up, down, left, right, stop;

		// Liste des rigidbody sélectionnés pour le contrôle
		std::vector<Rigidbody*> selectedRigidbodies;

		void handleInput();
		// Mis à défaut sur false
		Controller() : up(false), down(false), left(false), right(false), stop(false) {}

		void update(float deltaTime) {
			for (auto& rb : selectedRigidbodies) {
				rb->update(deltaTime);
			}
		}

		// Méthodes pour sélectionner et désélectionner des rigidbody
		void selectRigidbody(Rigidbody* rb) {
			selectedRigidbodies.push_back(rb);
		}

		void deselectRigidbody(Rigidbody* rb) {
			selectedRigidbodies.erase(std::remove(selectedRigidbodies.begin(), selectedRigidbodies.end(), rb), selectedRigidbodies.end());
		}

		// getters et setters
		float getBaseAcceleration() const { return base_acceleration; }
		void setBaseAcceleration(float acceleration) { base_acceleration = acceleration; }
};