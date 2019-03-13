#include "wplanner.h"

Wplanner::Wplanner(){


}

Wplanner::~Wplanner(){

}


void  Wplanner::msgFromplanner(){

   //QObject* object = QObject::sender(); //Returns a pointer to the object that sent the signal
   //socketP = static_cast<QTcpSocket*>(object); //explicit type conversion from the QObject* to the QTcpSocket*
   QByteArray msg = socketP -> readAll();
   /*
   if(Data=="e"){
           foreach(QByteArray i,socketFamiliar.keys()){
               socketFamiliar[i]->close(); // close all connected CUnits sockets
           }
           socketFamiliar.clear(); //Removes all items from the map socketFamiliar
        qDebug()<< "Expected disconnection with Planner";
        socketP->close(); // close Planner socket
        newsocket->close(); //?
        count = 0;
   }

   else{
     */
   QByteArray name, message; // name of CUnit and Mesage for it
   QStringList w=QString(msg).split(":");
   name = w.at(0).toLocal8Bit().constData();
   message =  w.at(1).toLocal8Bit().constData();

//перенести в rca?
   QMap<QByteArray,QTcpSocket*>::const_iterator i = socketFamiliar.find(name);
   //neeed to send a message to socket  i.value()
   i.value()->write(message);
   i.value()->waitForBytesWritten(500);
   }
}
