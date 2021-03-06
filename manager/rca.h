#ifndef RCA_H
#define RCA_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QSet>
#include <QMap>
#include <QPair>
#include <QString>
#include <QSharedPointer>
#include "connectors/wplanner.h"
#include "connectors/wcu.h"
#include "connectors/w3dscene.h"



class Rca: public QTcpServer
{
    Q_OBJECT

public:
    Rca();
    Rca(W3dscene s);
    ~Rca();
    Rca(const Rca&) = delete;
    Rca& operator=(const Rca&) = delete;
    Rca(Rca&&)  = delete;
    Rca& operator=(Rca&&) = delete;
private:
    QTcpSocket* socket;
    QTcpSocket* newsocket;
    W3dscene *scene;
    Wplanner planner;
    QSet<QTcpSocket*> socketNobody;
    QMap<QByteArray,Wcu*> units;
public slots:

    void incomingConnection(int socketDescriptor);
    void sockReady();
//    void sockDisc();
    void FromPlannerToCu(QByteArray name, QByteArray msg);
};

#endif // RCA_H
