#include "rca.h"

Rca::Rca(){}
Rca::~Rca(){}


void Rca::startRca()
{
    socket1 = new QTcpSocket(this);

    socket1->connectToHost("127.0.0.1", 9093); //connect to 3Dscene
    connect(socket1, &QTcpSocket::readyRead, this, &Rca::sockReady1);
    connect(socket1, &QTcpSocket::disconnected, this, &Rca::sockDisc1);
    //*connect(butt,&QPushButton::clicked,this,&MyClass::incCounter);

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

void Rca:: incomingConnection( int socketDescriptor )
{
    //nextPendingConnection()-? return virtual QTcpSocket *
    socket = new QTcpSocket(this);
    socket -> setSocketDescriptor( socketDescriptor ); //set uniqe number
    socketNobody.insert(socket); //set of sockets

    connect(socket, &QTcpSocket::readyRead, this, &Rca::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &Rca::sockDisc);

    qDebug()<< socketDescriptor<<"New client connected\n";
    qDebug()<< "The number of client: "<<socketNobody.size();

    // sendToClient(pClientSocket, "Server Response: Connected!");

}


void Rca::sockReady()
{
    QObject* object = QObject::sender();
    newsocket = static_cast<QTcpSocket*>(object);
    Data = socket -> readAll();

   // qDebug()<<"Data:"<< Data;

    if(Data=="p"){

        socketP=newsocket;
        socketNobody.erase(socketNobody.find(newsocket));//?
        qDebug()<< "Find the Planner!";

    }
    else{
        if((Data=="e")&&(socketP==newsocket)){
                foreach(int i,socketFamiliar.keys()){
                    socketFamiliar[i].first->close();
                    socketFamiliar.remove(i);
                }
             qDebug()<< "Expected disconnection with Planner";
             socketP->close();//?
             newsocket->close();//?

        }
        else{
             socketFamiliar.insert(count, qMakePair(newsocket, Data));
             socketNobody.erase(socketNobody.find(newsocket));
             qDebug()<< "Find the CUnit: "<< Data;;

        }
    }

   /* doc = QJsonDocument::fromJson(Data, &docerror);
    if(docerror.errorString().toInt() == QJsonParseError::NoError)//если ошибок нет
    {
        if(doc.object().value("id").toString()=="SomeData")//если параметры совпадают, то соединение c cunit прошло успешно ??
        {
           qDebug()<< "Connection";
           QByteArray itog = "{\"id\":\"SomeData\"}";
           //отправка на 3Dscene
           socket1 ->write(itog);
           socket1->waitForBytesWritten(500);
        }
        else
        {
            if(doc.object().value("name").toString()=="message")//если параметры совпадают, то соединение с parant прошло успешно ??
            {
                qDebug()<< "Connection";
                QByteArray itog = "{\"name\":\"message\"}";
                //как понять по какому соедиению отправлять сообщение ??
                socket ->write(itog);
                socket->waitForBytesWritten(500);

            }
            else
            {
                qDebug()<<"Wrong data transfer format";
            }
        }
    }*/
}

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

void Rca::sockReady1()
{
    if(socket->waitForConnected(3000))
    {
        qDebug()<<"Connection with 3Dscene!";
    }
}
