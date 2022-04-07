#include "BlockFinder.h"
BlockFinder::BlockFinder(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mainWidget = new MainWidget;
    setCentralWidget(mainWidget);
}
