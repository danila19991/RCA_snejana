#include "wcu.h"



Wcu::Wcu(QTcpSocket* socketn, QString name){
    socket = socketn;
    Name = name;
    connect(socket, &QTcpSocket::readyRead, this, &Wcu::msgFromCunit);//?
    connect(socket, &QTcpSocket::disconnected, this, &Wcu::sockDisc);//?
    connection = true;
}

Wcu::~Wcu(){

    }

// client is disconnected
void Wcu::sockDisc(){
    qDebug()<<"Disconnect";
    socket ->deleteLater();
}

bool Wcu::changeSocket(QTcpSocket* newsocket){
    if(connection){
        return false;
     }
    else{
        socket = newsocket;
        connection = true;
        return true;
    }
}

void Wcu::msgToCunit(QByteArray msg){
    socket->write(msg);
}

void Wcu::msgFromCunit(){
   QByteArray msg = socket -> readAll();
   msg.chop(1);
   emit signalMsgFromCu(msg);
}
