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

struct Pair{
    public:
           Pair(QByteArray name,QByteArray message):Name(name), Message(message) {}
    private:
           QByteArray Name, Message;

};

class Wplanner
{
    Q_OBJECT

public:
    Wplanner();
    ~Wplanner();
    Wplanner(QTcpSocket* socket);
    Wplanner(const Wplanner&) = delete;
    Wplanner& operator=(const Wplanner&) = delete;
    Wplanner(Wplanner&&)  = delete;
    Wplanner& operator=(Wplanner&&) = delete;
    bool changeSocket(QTcpSocket* socketn);
    void shutdown();
private:
    QTcpSocket* socketP;                                
public slots:
    void sockReady();
    void sockDisc();
    Pair msgFromPlanner();
signals:
    void signalMsgFromPl(QByteArray a1, QByteArray a2);

};

#endif // WPLANNER_H
