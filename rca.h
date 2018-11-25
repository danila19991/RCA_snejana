#ifndef RCA_H
#define RCA_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <Qset>
#include <Qmap>
#include <QPair>

const int cl = 3;

class Rca: public QTcpServer
{
    Q_OBJECT

public:
    Rca();
    ~Rca();
    void manager(QByteArray, QTcpSocket*);
    void messfromplanner(QByteArray mess);
    void messfromCunit(QByteArray mess);
private:
    QTcpSocket* socket;
    QTcpSocket* socket1;
    QTcpSocket* socketP;
    QTcpSocket* newsocket;
    QSet<QTcpSocket*> socketNobody;
   // QMap<int, QPair<QTcpSocket*, QByteArray>> socketFamiliar;
    QMap<QByteArray,QTcpSocket*> socketFamiliar;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docerror;
    int count = 0;

public slots:

    void incomingConnection(int socketDescriptor); 
    void sockReady();
    void sockDisc();
    void sockReady1();
    void sockDisc1();
};

#endif // RCA_H
