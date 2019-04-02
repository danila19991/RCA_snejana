#include "connectors/wcu.h"



Wcu::Wcu(QTcpSocket* socketn, QString name){
    socket = socketn;
    Name = name;
    connect(socket, &QTcpSocket::readyRead, this, &Wcu::msgFromCunit);
    connect(socket, &QTcpSocket::disconnected, this, &Wcu::sockDisc);
    connection = true;

}

Wcu::~Wcu(){

    }

// client is disconnected
void Wcu::sockDisc(){
    qDebug()<<"CUnit Disconnect";
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
    qDebug()<<"Recive msg to Cunit: "<<msg;

}

void Wcu::msgFromCunit(){
   QByteArray msg = socket -> readAll();
   if (msg =="") {
       qDebug()<<"Recive empty msg from Cunit";
   }
   else{
       qDebug()<<"Recive msg from Cunit: "<<msg;
       msg.chop(1);
       //qDebug()<<"Msg from Cunit after chop: "<<msg;
       emit signalMsgFromCu(msg);
   }
}
