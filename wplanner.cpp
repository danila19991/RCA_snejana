#include "wplanner.h"


Wplanner::Wplanner(QTcpSocket* socket)
{
    socketP = socket;
}

Wplanner::~Wplanner(){

}

 bool Wplanner::changeSocket(QTcpSocket* socketn){
     if(socketn == socketP){
     return false;
     }
 else{
        socketP = socketn;
        //delete socketn;//?
        return true;
    }
 }

void  Wplanner:: shutdown(){
    //?
   socketP->close();
}

Pair  Wplanner::msgFromPlanner(){
   QByteArray msg = socketP -> readAll();//?

   if(msg=="e"){
           shutdown();
   }
   else{
   QByteArray name, message; // name of CUnit and Mesage for it
   QStringList w=QString(msg).split(":");
   QStringList q=w.at(1).split("|");
   name = w.at(0).toLocal8Bit().constData();
   message =  q.at(1).toLocal8Bit().constData();
   return  Pair(name,message);
   }
}
