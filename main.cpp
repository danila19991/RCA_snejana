#include <QCoreApplication>
#include "rca.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Rca rca;
    rca.startRca();
    return a.exec();
}
