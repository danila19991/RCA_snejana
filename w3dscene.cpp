#include "w3dscene.h"

//при инициализации подключается к 3d scene
W3dscene::W3dscene(){


}
W3dscene::W3dscene(QTcpSocket* socketn, int port)
{
    Port = port;
    socket = socketn;
    socket->connectToHost("127.0.0.1", 9093); //connect to 3Dscene
}

W3dscene::~W3dscene(){

}

// 3Dscene is disconnected
void W3dscene::sockDisc1(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}

void W3dscene::sockReady1(){
    if(socket->waitForConnected(3000))
    {
        qDebug()<<"Connection with 3Dscene!";
    }
}

void W3dscene::sendto3dscene(QByteArray msg){
    msg.prepend("{");
    msg.append("}");
    socket->write(msg); //sent JSON to 3dscene, soket1 from class w3dscene
}
