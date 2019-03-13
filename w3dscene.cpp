#include "w3dscene.h"

//при инициализации подключается к 3d scene
W3dscene::W3dscene(){


}
W3dscene::W3dscene(QTcpSocket* socketn, int port) //+port -socket ??
{
    Port = port;
    count = 0;
    socket = socketn;
    socket->connectToHost("127.0.0.1", 9093); //connect to 3Dscene
    //newsocket = new QTcpSocket;
    //socketNobody = QSet<QTcpSocket*>();
    //socketFamiliar = QMap<QByteArray,QTcpSocket*>();
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
//слот для отправки сообщений на 3dscene
void W3dscene::sendto3dscene(QTcpSocket* socket1, QByteArray msg){

    socket1->write(msg);
}
