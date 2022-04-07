#include "BlockXplorer.h"

void BlockXplorer::setupVerticalBox()
{
	verticalBox = new QGroupBox("Options");
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(new QPushButton("Button 1"));
	layout->addWidget(new QPushButton("Button 2"));
	verticalBox->setLayout(layout);
}

BlockXplorer::BlockXplorer(QWidget* parent):QMainWindow(parent)
{
	ui.setupUi(this);
	setupVerticalBox();
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(verticalBox);
	setLayout(mainLayout);
}
