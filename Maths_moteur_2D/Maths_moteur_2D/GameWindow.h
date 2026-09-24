#pragma once
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Controller.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
    
		// Contrôle les objets sélectionnés, en fonction des entrées de l'utilisateur (clavier)
    Controller controller = Controller();

    // On utilise une horloge pour gérer le temps écoulé entre les mises à jour du jeu
    int fps = 50; // Nombre de mises à jour par seconde
    float dt = 1.0f / fps; // Temps écoulé entre les mises à jour (en secondes)
    QTimer* timer = nullptr; // initialisé dans le constructeur


public:
    GameWindow(QWidget* parent = nullptr);
    virtual ~GameWindow();

    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
private slots:
    void updateGame(); // Met à jour l'état du jeu en fonction du temps écoulé
};

#endif