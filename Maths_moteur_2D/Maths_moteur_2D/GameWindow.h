#pragma once
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include "Controller.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
    
		// Contrôle les objets sélectionnés, en fonction des entrées de l'utilisateur (clavier)
    Controller controller = Controller();

public:
    GameWindow(QWidget* parent = nullptr);
    virtual ~GameWindow();

    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
};

#endif

