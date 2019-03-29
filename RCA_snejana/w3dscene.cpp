#include "w3dscene.h"

//при инициализации подключается к 3d scene
W3dscene::W3dscene(){
connection = false;
}

W3dscene::~W3dscene(){

}

// 3Dscene is disconnected
void W3dscene::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
    connection = false;
}

void W3dscene::sendto3dscene(QByteArray msg){
    msg.prepend("{");
    msg.append("}");
    socket->write(msg); //sent JSON to 3dscene, soket1 from class w3dscene
}
W3dscene::W3dscene(int port){
        socket = new QTcpSocket(this);
        Port = port;
        connect(socket, &QTcpSocket::disconnected, this, &W3dscene::sockDisc);
        socket->connectToHost("127.0.0.1", 9093); //connect to 3Dscene
        connection = true;
}
