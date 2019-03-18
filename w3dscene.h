#ifndef W3DSCENE_H
#define W3DSCENE_H
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


class W3dscene
{
    Q_OBJECT

public:

    W3dscene();
    W3dscene(QTcpSocket* socketn, int port); //+port -socket ??
    ~W3dscene();
    W3dscene(const W3dscene&) = delete;
    W3dscene& operator=(const W3dscene&) = delete;
    W3dscene(W3dscene&&)  = delete;
    W3dscene& operator=(W3dscene&&) = delete;

private:

    QTcpSocket* socket;
    int Port;

public slots:
    void sendto3dscene(QByteArray msg);
    void sockReady1();
    void sockDisc1();

};


#endif // W3DSCENE_H
