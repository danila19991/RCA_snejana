#include "wcu.h"



Wcu::Wcu(QTcpSocket* socketn, QByteArray data)
{
    socket = socketn;
    Data = data;
    count = 0;
}

// client is disconnected
void Wcu::sockDisc()
{
    qDebug()<<"Disconnect";
    socket ->deleteLater();
}
void Wcu::msgFromCunit()
{
    QObject* object = QObject::sender(); //Returns a pointer to the object that sent the signal
    socket  = static_cast<QTcpSocket*>(object); //explicit type conversion from the QObject* to the QTcpSocket*
    QByteArray msg = socket  -> readAll();

    msg.prepend("{");
    msg.append("}");

    //connect(this,SIGNAL(signalMsgFromCu(int)), this, &W3dscene::sendto3dscene(socket1,msg));
    // void sendto3dscene(QTcpSocket* socket1, QByteArray msg);
    //emit signalMsgFromCu(int);
    socket->write(msg); //sent JSON to 3dscene, soket1 from class w3dscene

}
