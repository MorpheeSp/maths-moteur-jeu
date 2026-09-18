#pragma once
#include "Rigidbody.h"

// Classe qui sélectionne un ou plusieurs rigidbody et contrôle leur mouvement en fonction des entrées de l'utilisateur (clavier, souris, etc.)
class Controller
{
	std::vector<Rigidbody*> selectedRigidbodies;

	public:
		// Flags pour garder en mémoire l'état des touches de direction
		bool up, down, left, right, stop;

		void handleInput();
		// Mis à défaut sur false
		Controller() : up(false), down(false), left(false), right(false), stop(false) {}

};