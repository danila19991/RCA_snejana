#ifndef WCU_H
#define WCU_H

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

class Wcu:  public QTcpServer
{
    Q_OBJECT

public:
    Wcu();
    Wcu(QTcpSocket* socketn, QByteArray data);
    ~Wcu();
    Wcu(const Wcu&) = delete;
    Wcu& operator=(const Wcu&) = delete;
    Wcu(Wcu&&)  = delete;
    Wcu& operator=(Wcu&&) = delete;

private:
    QTcpSocket* socket;
    int count = 0;
    QByteArray Data;
    //QTcpSocket* newsocket;
    //QSet<QTcpSocket*> socketNobody;
    //QMap<QByteArray,QTcpSocket*> socketFamiliar;

public slots:
    void sockReady();
    void sockDisc();
    void msgFromCunit();
signals:
    void signalMsgFromCu(QByteArray);
};

#endif // WCU_H
