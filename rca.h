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
#include "wcu.h"
#include "wplanner.h"
#include "W3dscene.h"



class Rca: public QTcpServer
{
    Q_OBJECT

public:
    Rca();
    ~Rca();
    Rca(const Rca&) = delete;
    Rca& operator=(const Rca&) = delete;
    Rca(Rca&&)  = delete;
    Rca& operator=(Rca&&) = delete;
private:
    QTcpSocket* socket;
    QTcpSocket* newsocket;
    W3dscene scene;
    QSet<QTcpSocket*> socketNobody;
    QMap<QByteArray,Wcu> units;
public slots:

    void incomingConnection(int socketDescriptor); 
    void sockReady();
    void sockDisc();

};

#endif // RCA_H
