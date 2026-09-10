#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Mm2D.h"

class Mm2D : public QMainWindow
{
    Q_OBJECT

public:
    Mm2D(QWidget *parent = nullptr);
    ~Mm2D();

private:
    Ui::Mm2DClass ui;
};

