#include "enigmasimulator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnigmaSimulator w;
    w.show();
    return a.exec();
}
