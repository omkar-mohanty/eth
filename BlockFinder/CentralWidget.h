#pragma once
#include<qwidget.h>
#include<qboxlayout.h>
#include<qpushbutton.h>

class ButtonPage : public QWidget {
public:
	ButtonPage(QWidget* parent = Q_NULLPTR);
private:
	QVBoxLayout* layout;
};

class MainWidget : public QWidget {
public:

	MainWidget(QWidget* parent = Q_NULLPTR);

private:
	QHBoxLayout* layout;
};