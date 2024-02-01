#include "worker.h"

Worker::Worker()
{

}

void Worker::start(int n) {
    n_ = n;
    running_ = true;
    thread_ = std::thread(&Worker::work, this);
}

void Worker::stop() {
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

void Worker::work() {
    QUdpSocket socket_;
    std::stack<int, std::vector<int>> container;
    std::mutex m;
    for (int i = 0; i < n_ && running_; i++) {
        int value = rand() % 100;
        m.lock();
        container.push(value);
        //std::cout << value << '\n';
        m.unlock();
    }

    for (int i = 0; i < n_ && running_; i++) {
        m.lock();
        if (!container.empty()) {
            int value = container.top();
            container.pop();
            m.unlock();
            QByteArray byteArray;
            QDataStream stream(&byteArray, QIODevice::WriteOnly);
            stream << QString::number(value);
            stream << QDateTime::currentDateTime().toString(Qt::ISODate);

            m.lock();
            socket_.writeDatagram(byteArray, QHostAddress::LocalHost, 4321);
            m.unlock();
        } else {
            m.unlock();
            qDebug()<<"Container is empty";
        }
    }
}

