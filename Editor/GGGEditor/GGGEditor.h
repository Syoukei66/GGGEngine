#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GGGEditor.h"

class GGGEditor : public QMainWindow
{
    Q_OBJECT

public:
    GGGEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::GGGEditorClass ui;
};
