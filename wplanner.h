#ifndef WPLANNER_H
#define WPLANNER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPair>
#include <QString>
#include <QSharedPointer>



class Wplanner: public QTcpServer
{
    Q_OBJECT

public:
    Wplanner();
    //Wplanner(QTcpSocket* socket);
    ~Wplanner();
    Wplanner(const Wplanner&) = delete;
    Wplanner& operator=(const Wplanner&) = delete;
    Wplanner(Wplanner&&)  = delete;
    Wplanner& operator=(Wplanner&&) = delete;
    bool changeSocket(QTcpSocket* socketn);
    void shutdown();
private:
    QTcpSocket* socketP;
    bool connection;
public slots:
    void sockDisc();
    void msgFromPlanner();
signals:
    void signalMsgFromPl(QByteArray name, QByteArray msg);

};

#endif // WPLANNER_H
