#ifndef WPLANNER_H
#define WPLANNER_H

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

class Wplanner
{
    Q_OBJECT

public:
    Wplanner();
    ~Wplanner();
    Wplanner(QTcpSocket* socketn)
    {
        socketP = socketn;
        count = 0;
        //Data = data;
        //newsocket = new QTcpSocket;
        //socketNobody = QSet<QTcpSocket*>();
        //socketFamiliar = QMap<QByteArray,QTcpSocket*>();
    }
    Wplanner(const Wplanner&) = delete;
    Wplanner& operator=(const Wplanner&) = delete;
    Wplanner(Wplanner&&)  = delete;
    Wplanner& operator=(Wplanner&&) = delete;
    bool changeSocket(QTcpSocket* socketn);

private:
    QTcpSocket* socketP;
    int count = 0;
    //QTcpSocket* newsocket;
    //QSet<QTcpSocket*> socketNobody;
    //QMap<QByteArray,QTcpSocket*> socketFamiliar;
    //QByteArray Data;


public slots:
    void sockReady();
    void sockDisc();
    void msgFromplanner();
signals:
    void signalMsgFromPl(QByteArray a1, QByteArray a2);

};

#endif // WPLANNER_H
