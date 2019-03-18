#include "wplanner.h"


Wplanner::Wplanner(QTcpSocket* socket)
{
    socketP = socket;
    connect(socketP, &QTcpSocket::readyRead, this, &Wplanner::msgFromPlanner);//?
    connect(socketP, &QTcpSocket::disconnected, this, &Wplanner::sockDisc);//?
    connection = true;
}

Wplanner::~Wplanner(){

}

// planner is disconnected
void Wplanner::sockDisc(){
    qDebug()<<"Disconnect";
    connection = false;
}

 bool Wplanner::changeSocket(QTcpSocket* newsocket){
    if(connection){
        return false;
     }
    else{
        socketP = newsocket;
        connect(socketP, &QTcpSocket::readyRead, this, &Wplanner::msgFromPlanner);//?
        connect(socketP, &QTcpSocket::disconnected, this, &Wplanner::sockDisc);//?
        connection = true;
        return true;
    }
 }

void  Wplanner:: shutdown(){
    //?
   socketP->close();
}

void  Wplanner::msgFromPlanner(){
   QByteArray msg = socketP -> readAll();

   if(msg=="e"){
        shutdown();
   }
   else{
        QByteArray name, message; // name of CUnit and Mesage for it
        QStringList w=QString(msg).split(":");
        QStringList q=w.at(1).split("|");
        name = w.at(0).toLocal8Bit().constData();
        message =  q.at(1).toLocal8Bit().constData();
        emit signalMsgFromPl(name, message);
   }
}
