#ifndef WCU_H
#define WCU_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPair>
#include <QString>
#include <QSharedPointer>


class Wcu:  public QTcpServer
{
    Q_OBJECT

public:
    Wcu();
    Wcu(QTcpSocket* socketn, QString name);
    ~Wcu();
    Wcu(const Wcu&) = delete;
    Wcu& operator=(const Wcu&) = delete;
    Wcu(Wcu&&)  = delete;
    Wcu& operator=(Wcu&&) = delete;
    bool changeSocket(QTcpSocket* socketn);

private:
    QTcpSocket* socket;
    QString Name;
    bool connection;

public slots:
//    void sockReady();
    void sockDisc();
    void msgToCunit(QByteArray msg);
    void msgFromCunit();
signals:
    void signalMsgFromCu(QByteArray);
};

#endif // WCU_H
