#include "connectors/wplanner.h"


Wplanner::Wplanner()
{
    connection = false;
}

Wplanner::~Wplanner(){

}

// planner is disconnected
void Wplanner::sockDisc(){
    qDebug()<<"Planner disconnect";
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
        qDebug()<<"Planner connected";
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
        qDebug()<<"E is comming";
        shutdown();
   }
   else{
        qDebug()<<" MSG from Planner to Cu";
        QByteArray name, message; // name of CUnit and Mesage for it
        QStringList w=QString(msg).split(":");
        //qDebug()<<" MSG from Planner to Cu"<<w.at(0)<<" "<<w.at(1);
        QStringList q=w.at(1).split("|");
        name = w.at(0).toLocal8Bit().constData();
        message =  q.at(0).toLocal8Bit().constData();
        //qDebug()<<"emit signal";
        emit signalMsgFromPl(name, message);

   }
}
