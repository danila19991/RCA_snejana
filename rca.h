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
#include <QString>
#include <QSharedPointer>

const int cl = 3;

class Rca: public QTcpServer
{
    Q_OBJECT

public:
    Rca();
    ~Rca();
    void manager(QByteArray, QTcpSocket*);
    Rca(const Rca&) = delete;
    Rca& operator=(const Rca&) = delete;
    Rca(Rca&&)  = delete;
    Rca& operator=(Rca&&) = delete;

private:
    //QSharedPointer<QTcpSocket> socket(new QTcpSocket);
    QTcpSocket* socket;
    QTcpSocket* socket1;
    QTcpSocket* socketP;
    QTcpSocket* newsocket;
    QSet<QTcpSocket*> socketNobody;
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
    void msgFromPlanner();
    void msgFromCunit();
};

#endif // RCA_H
