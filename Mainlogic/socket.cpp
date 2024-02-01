#include "socket.h"

Socket::Socket(int port):socket_(new QUdpSocket()) {
    if (!socket_->bind(port)) {
        throw std::runtime_error("Failed to bind socket");
    }
}

bool Socket::hasPendingDatagrams() {
    return socket_->hasPendingDatagrams();
}



std::pair<QString, QString> Socket::readDatagram() {
    QByteArray receivedData;
    receivedData.resize(socket_->pendingDatagramSize());

    if (socket_->readDatagram(receivedData.data(), receivedData.size()) == -1) {
        throw std::runtime_error("Failed to read datagram");
    }

    QDataStream inStream(receivedData);

    QString receivedText;
    QString t;
    inStream >> receivedText >> t;
    return {receivedText, t};
}



void Socket::writeDatagram(const QString& text, const QString& t, int port) {
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << text;
    stream << t;
    if (socket_->writeDatagram(byteArray, QHostAddress::LocalHost, port) == -1) {
        throw std::runtime_error("Failed to write datagram");
    }
}



Socket::~Socket() {
    if (socket_) {
        socket_->close();
        delete socket_;
    }
}
