#include "feigemainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FeigeMainWindow w;
    w.show();
    return a.exec();
}
