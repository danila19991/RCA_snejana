#include "rca.h"
#include "W3dscene.h"


Rca::Rca(){
    socket1 = new QTcpSocket(this);
    W3dscene w3dscene(socket1, 9093);
    connect(socket1, &QTcpSocket::readyRead, w3dscene, &W3dscene::sockReady1);//?
    connect(socket1, &QTcpSocket::disconnected, w3dscene, &W3dscene::sockDisc1);//?

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
    connect(socket, &QTcpSocket::disconnected, this, &Rca::sockDisc);

    qDebug()<< socketDescriptor<<"New client connected\n";
    qDebug()<< "The number of client: "<<socketNobody.size();

}



void Rca::sockReady()
{
    QObject* object = QObject::sender(); //Returns a pointer to the object that sent the signal
    newsocket = static_cast<QTcpSocket*>(object); //explicit type conversion from the QObject* to the QTcpSocket*
    Data = socket -> readAll();


    if(Data=="p"){ //the name of the planner came
        //Wplanner(newsocket);
        socketP=newsocket; //удалить
        socketNobody.erase(socketNobody.find(newsocket));//remove the socket from the list of undefined
        qDebug()<< "Find the Planner!";
        disconnect(newsocket, &QTcpSocket::readyRead, this, &Rca::sockReady);//удалить - ?
        connect(newsocket, &QTcpSocket::readyRead, this, &Rca::msgFromPlanner);//удалить - ?

    }
    else{
            //if the message passes an unknown socket
           // if(!socketNobody.contains(newsocket))

          //then the name came from an unfamiliar socket
          socketFamiliar.insert(Data, newsocket); //add it to Familiar
          socketNobody.erase(socketNobody.find(newsocket)); //remove from the list of unknown
          qDebug()<< "Find the CUnit: "<< Data;;
          disconnect(newsocket, &QTcpSocket::readyRead, this, &Rca::sockReady);
          connect(newsocket, &QTcpSocket::readyRead, this, &Rca::msgFromCunit);


    }


}

