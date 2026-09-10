#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Maths_moteur_2D.h"

class Maths_moteur_2D : public QMainWindow
{
    Q_OBJECT

public:
    Maths_moteur_2D(QWidget *parent = nullptr);
    ~Maths_moteur_2D();

private:
    Ui::Maths_moteur_2DClass ui;
};

