#include "rca.h"

Rca::Rca(){}
Rca::~Rca(){}
int b = 0; // для записи имён
void Rca::startRca()
{
    socket1 = new QTcpSocket(this);
    //исправить адрес и порт
    socket1->connectToHost("127.0.0.1", 5555); //подключение к 3Dscene
    connect(socket1, SIGNAL(readyRead()), this, SLOT(sockReady1()));
    connect(socket1, SIGNAL(disconnected()), this, SLOT(sockDisc1()));
    //ждем подключения остальных
    if(this->listen( QHostAddress::Any, 5555 ))
    {
        qDebug()<<"Listening";
    }
    else
    {
         qDebug()<<"Not listening";
    }
}

void Rca:: incomingConnection( int socketDescriptor )
{
    socket = new QTcpSocket(this);
    socket -> setSocketDescriptor( socketDescriptor ); //присваиваем уникальный номер
    if(b < 3){ nconnect[b]=socketDescriptor;} // попытка связать имена с номерами соединений массив name, но не факт, что это работает
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
    qDebug()<< socketDescriptor<<"Client connected";

    //формат json пара ключ, значение "key":"value"
    //socket -> write("You are connect"); //отсылаем клиенту
   // socket -> write("{\"id\":\"SomeData\"}");
    //qDebug()<<"Send client connect status - YES";

}

//метод описывающий готовность rca  принимать данные
void Rca::sockReady()
{
    Data = socket -> readAll(); // вопрос что мы прочитаем имена по очереди или всё сразу имя, данные?
    qDebug()<<"Data:"<<Data; //вывели полученное имя, вопрос что с ним дальше делать? я записываю именна в массив
    if(Data=="e"){
        //возможно вызвать  socket ->deleteLater(); что делать с именем?
    }
    else{
         if(b < 3){
         name[b]=Data;
            b++;
         }
    }
    /*doc = QJsonDocument::fromJson(Data, &docerror);
    //вид команды от киента Cunit: "id":"SomeData"
    if(docerror.errorString().toInt()==QJsonParseError::NoError)
    {
        if(doc.object().value("id").toString()=="SomeData")//если параметры совпадают, то соединение прошло успешно
        {
            QFile file;
            file.setFileName("C:\\Qt\\workers.json");
            if(file.open(QIODevice::ReadOnly|QFile::Text))
            {
                QByteArray fromfile = file.readAll();
                QByteArray itog = "{\"id\":\"resultselect\",\"result\":" +fromfile+"}";
                socket ->write(itog);
                socket->waitForBytesWritten(500);
            }
            file.close();
        }
        else
        {
            //QMessageBox::information(this, "Информация:", "Ошибки с форматом передачи данных"+docerror.errorString());
        }
    }*/
    doc = QJsonDocument::fromJson(Data, &docerror);
    if(docerror.errorString().toInt()==QJsonParseError::NoError)//если ошибок нет
    {
        if(doc.object().value("id").toString()=="SomeData")//если параметры совпадают, то соединение c cunit прошло успешно ??
        {
           qDebug()<< "Соединение установлено";
           QByteArray itog = "{\"id\":\"SomeData\"}";
           //отправка на 3Dscene
           socket1 ->write(itog);
           socket1->waitForBytesWritten(500);
        }
        else
        {
            if(doc.object().value("name").toString()=="message")//если параметры совпадают, то соединение с parant прошло успешно ??
            {
                qDebug()<< "Соединение установлено";
                QByteArray itog = "{\"name\":\"message\"}";
                //как понять по какому соедиению отправлять сообщение ??
                socket ->write(itog);
                socket->waitForBytesWritten(500);

            }
            else
            {
                qDebug()<<"Ошибки с форматом передачи данных";
            }
        }
    }
}
//оповещаем клиента на стороне сервера, что кто-то отсоединился
void Rca::sockDisc()
{
    qDebug()<<"Disconnect";
    socket ->deleteLater();
}

void Rca::sockDisc1()
{
    qDebug()<<"Disconnect";
    socket1->deleteLater();
}

void Rca::sockReady1()
{
    if(socket->waitForConnected(500))
    {

        socket->waitForReadyRead(500);//возможно это строчка не нужна, так как нам ничего отпрадять не должны
        //если соединение установлено, то выведем сообщение от 3Dscene,
       // Data = socket->readAll();
        qDebug()<<"Соединение с 3Dscene установлено ";

    }
}
