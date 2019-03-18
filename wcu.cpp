#include "wcu.h"



Wcu::Wcu(QTcpSocket* socketn, QString name)
{
    socket = socketn;
    Name = name;
}

// client is disconnected
void Wcu::sockDisc()
{
    qDebug()<<"Disconnect";
    socket ->deleteLater();
}
void Wcu::msgToCunit(QByteArray msg)
{
    socket->write(msg);
}
QByteArray Wcu::msgFromCunit(){
   QByteArray msg = socket -> readAll();
   msg.chop(1);
   return msg;
}
