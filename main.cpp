#include "Chess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vue::Chess w;
    w.show();
    return a.exec();
}
