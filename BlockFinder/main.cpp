#include "BlockFinder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlockFinder w;
    w.show();
    return a.exec();
}
