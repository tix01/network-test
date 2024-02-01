#ifndef SOCKET_H
#define SOCKET_H

#include <QUdpSocket>
#include <QHostAddress>

class Socket
{
public:
    Socket(int port);
    bool hasPendingDatagrams();
    std::pair<QString, QString> readDatagram();
    void writeDatagram(const QString& text, const QString& t, int port);
    ~Socket();
private:
    QUdpSocket* socket_;
};

#endif // SOCKET_H
