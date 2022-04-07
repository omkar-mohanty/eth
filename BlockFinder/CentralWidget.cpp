#include "CentralWidget.h"
#include<qboxlayout.h>



ButtonPage::ButtonPage(QWidget* parent)
{
	layout = new QVBoxLayout;
	layout->addWidget(new QPushButton("Block Number"));
	layout->addWidget(new QPushButton("Block Number"));
	setLayout(layout);
}

MainWidget::MainWidget(QWidget* parent):QWidget(parent)
{
	layout = new QHBoxLayout;
	ButtonPage* buttonPage = new ButtonPage;
	layout->addWidget(buttonPage);
	setLayout(layout);
}
