#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BlockXplorer.h"
#include<qvector.h>
#include<qwidget.h>
#include<qgroupbox.h>
#include<qboxlayout.h>
#include<qpushbutton.h>
class BlockXplorer : public QMainWindow
{
    Q_OBJECT
private:
    void setupVerticalBox();

public:
    BlockXplorer(QWidget *parent = Q_NULLPTR);

private:
    Ui::BlockXplorerClass ui;
    QGroupBox* verticalBox;
 };
