#include "addressbook.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    addressbook w;
//    w.show();

    addressbook *addressBook = new addressbook;
    addressBook->show();

    return a.exec();
}
