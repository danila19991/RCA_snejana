#ifndef W3DSCENE_H
#define W3DSCENE_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPair>
#include <QString>
#include <QSharedPointer>


class W3dscene: public QTcpServer
{
    Q_OBJECT

public:

    W3dscene();
    W3dscene(int port);
    ~W3dscene();
    W3dscene(const W3dscene&) = delete;
    W3dscene& operator=(const W3dscene&) = delete;
    W3dscene(W3dscene&&)  = delete;
    W3dscene& operator=(W3dscene&&) = delete;


private:

    QTcpSocket* socket;
    int Port;
    bool connection;

public slots:
    void sendto3dscene(QByteArray msg);
    void sockDisc();

};


#endif // W3DSCENE_H
