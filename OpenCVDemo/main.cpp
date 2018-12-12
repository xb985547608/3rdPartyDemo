#include <QApplication>
#include "pictureprocesswidget.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    PictureProcessWidget w;
    w.show();

    return a.exec();
}
