#include "rca.h"



Rca::Rca(){
    socket1 = new QTcpSocket(this);

    socket1->connectToHost("127.0.0.1", 9093); //connect to 3Dscene
    connect(socket1, &QTcpSocket::readyRead, this, &Rca::sockReady1);
    connect(socket1, &QTcpSocket::disconnected, this, &Rca::sockDisc1);

    if(this->listen( QHostAddress::Any, 5555 ))
    {
        qDebug()<<"Listening";
    }
    else
    {
         qDebug()<<"Error! Unable to start the server:"
                << this->errorString();
    }
}

Rca::~Rca(){}

// client is disconnected
void Rca::sockDisc()
{
    qDebug()<<"Disconnect";
    socket ->deleteLater();
}
// 3Dscene is disconnected
void Rca::sockDisc1()
{
    qDebug()<<"Disconnect";
    socket1->deleteLater();
}

void Rca:: incomingConnection( int socketDescriptor )
{
    socket = new QTcpSocket(this);
    socket -> setSocketDescriptor( socketDescriptor ); //set uniqe number
    socketNobody.insert(socket); //set of sockets

    connect(socket, &QTcpSocket::readyRead, this, &Rca::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &Rca::sockDisc);

    qDebug()<< socketDescriptor<<"New client connected\n";
    qDebug()<< "The number of client: "<<socketNobody.size();

}

void Rca::sockReady1()
{
    if(socket->waitForConnected(3000))
    {
        qDebug()<<"Connection with 3Dscene!";
    }
}

 void  Rca::manager(QByteArray mess, QTcpSocket* s)
 {
     if(s==socketP)
     {
        messFromPlanner(mess);
     }
     else
     {
         messFromCunit(mess);
     }
 }

 void  Rca::messFromPlanner(QByteArray mess)
 {
    bool flag = true;
    QByteArray name, message; // name of CUnit and Mesage for it
    for (int i = 0; i < mess.size(); ++i) {

        if (mess.at(i) == ':')
        {
            flag = false;
            continue;
        }

        if (flag)
        {
            name.append(mess[i]);
        }
        else
        {
            message.append(mess[i]);
        }
     }
    QMap<QByteArray,QTcpSocket*>::const_iterator i = socketFamiliar.find("name");
    //neeed to send a message to socket  i.value()
    i.value()->write(message);
    i.value()->waitForBytesWritten(500);
 }

 void  Rca::messFromCunit(QByteArray mess)
 {
     bool flag = true;

     QByteArray id, SomeData;
     for (int i = 0; i < mess.size(); ++i) {

         if (mess.at(i) == ':')
         {
             flag = false;
             continue;
         }

         if (flag)
         {
             id.append(mess[i]);
         }
         else
         {
             SomeData.append(mess[i]);
         }
     }

     auto encodedID = id.toBase64();
     auto encodedSomeData = SomeData.toBase64();

     QJsonObject mess_obj;
     mess_obj.insert(QString::fromLatin1(encodedID),QJsonValue(QString::fromLatin1(encodedSomeData)));

     socket1->write(QJsonDocument(mess_obj).toJson(QJsonDocument::Indented));


 }
void Rca::sockReady()
{
    QObject* object = QObject::sender(); //Returns a pointer to the object that sent the signal
    newsocket = static_cast<QTcpSocket*>(object); //explicit type conversion from the QObject* to the QTcpSocket*
    Data = socket -> readAll();


    if(Data=="p"){ //the name of the planner came

        socketP=newsocket;
        socketNobody.erase(socketNobody.find(newsocket));//remove the socket from the list of undefined
        qDebug()<< "Find the Planner!";

    }
    else{
        if((Data=="e")&&(socketP==newsocket)){
                foreach(QByteArray i,socketFamiliar.keys()){
                    socketFamiliar[i]->close(); // close all connected CUnits sockets
                }
                socketFamiliar.clear(); //Removes all items from the map socketFamiliar
             qDebug()<< "Expected disconnection with Planner";
             socketP->close(); // close Planner socket
             newsocket->close();
             count = 0;

        }
        else{
            //if the message passes an unknown socket
            if(!socketNobody.contains(newsocket))
            {
                //then the name came from an unfamiliar socket
             socketFamiliar.insert(Data, newsocket); //add it to Familiar
             socketNobody.erase(socketNobody.find(newsocket)); //remove from the list of unknown
             qDebug()<< "Find the CUnit: "<< Data;;

            }
            else
            {
                //the message passes an Familiar socket
                manager(Data, newsocket);
            }

        }
    }


}

