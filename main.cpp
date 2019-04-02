#include <QCoreApplication>
#include "manager/rca.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Rca rca;

    return a.exec();
}
