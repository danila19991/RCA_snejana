#include "rca.h"


Rca::Rca(){

    scene.changeSocket(9093);

    connect(&planner, &Wplanner::signalMsgFromPl, this, &Rca::FromPlannerToCu);

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

Rca::~Rca(){

}


void Rca:: incomingConnection( int socketDescriptor )
{
    socket = new QTcpSocket(this);
    socket -> setSocketDescriptor( socketDescriptor ); //set uniqe number
    socketNobody.insert(socket); //set of sockets

    connect(socket, &QTcpSocket::readyRead, this, &Rca::sockReady);
//    connect(socket, &QTcpSocket::disconnected, this, &Rca::sockDisc);

    qDebug()<< socketDescriptor<<"New client connected\n";
    qDebug()<< "The number of client: "<<socketNobody.size();

}

 void Rca::FromPlannerToCu(QByteArray name,QByteArray message)
 {
     QMap<QByteArray,Wcu*>::const_iterator i = units.find(name);
     //neeed to send a message to socket  i.value()
     i.value()->msgToCunit(message);
     //i.value()->waitForBytesWritten(500);
 }
//*/
void Rca::sockReady()
{
    QObject* object = QObject::sender(); //Returns a pointer to the object that sent the signal
    newsocket = static_cast<QTcpSocket*>(object); //explicit type conversion from the QObject* to the QTcpSocket*
    QByteArray Data = newsocket -> readAll();


    if(Data=="p"){ //the name of the planner came
        if(planner.changeSocket(newsocket)){
            socketNobody.erase(socketNobody.find(newsocket));//remove the socket from the list of undefined
            disconnect(newsocket, &QTcpSocket::readyRead, this, &Rca::sockReady);
            qDebug()<< "Find the Planner!";
        }

    else{
          //then the name came from an unfamiliar socket
          //Wcu wcu(newsocket,Data);
          Wcu * pwcu = new Wcu(newsocket, Data);
          units.insert(Data, pwcu); //add it to Familiar
          socketNobody.erase(socketNobody.find(newsocket)); //remove from the list of unknown
          qDebug()<< "Find the CUnit: "<< Data;;
          disconnect(newsocket, &QTcpSocket::readyRead, this, &Rca::sockReady);
          connect(newsocket, &QTcpSocket::readyRead, pwcu, &Wcu::msgFromCunit);
          }
    }

}

