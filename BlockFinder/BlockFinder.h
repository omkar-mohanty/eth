#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BlockFinder.h"
#include"CentralWidget.h"
class BlockFinder : public QMainWindow
{
    Q_OBJECT

public:
    BlockFinder(QWidget *parent = Q_NULLPTR);

private:
    Ui::BlockFinderClass ui;
    MainWidget* mainWidget;
};
