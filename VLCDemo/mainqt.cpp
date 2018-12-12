#include <QApplication>
#include "vlcwidget.h"

int main (int argc, char** argv)
{
    QApplication a(argc, argv);

    VLCWidget w;
    w.show();

    return a.exec();
}
