#ifndef RCA_H
#define RCA_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <Qfile>

class Rca: public QTcpServer
{
    Q_OBJECT
public:
    Rca();
    ~Rca();
    QTcpSocket* socket;
    QTcpSocket* socket1;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docerror;
    QByteArray name[3];
    int nconnect[3];

public slots:
    void startRca();
    void incomingConnection(int socketDescriptor);
    void sockReady();
    void sockDisc();
    void sockReady1();
    void sockDisc1();
};

#endif // RCA_H
