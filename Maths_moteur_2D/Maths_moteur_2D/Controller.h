#pragma once
#include "Rigidbody.h"

// Classe qui sélectionne un ou plusieurs rigidbody et contrôle leur mouvement en fonction des entrées de l'utilisateur (clavier, souris, etc.)
class Controller
{
	std::vector<rigidbody*> selectedRigidbodies;

	public:
		bool up, down, left, right, stop;

		void handleInput();
		Controller() : up(false), down(false), left(false), right(false), stop(false) {}

};