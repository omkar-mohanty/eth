#include "BlockXplorer.h"
#include <QtWidgets/QApplication>
#include<qpushbutton.h>
void InitApp() {
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    BlockXplorer xplorer;
    xplorer.show();
    return a.exec();
}
