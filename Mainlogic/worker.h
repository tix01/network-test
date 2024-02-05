#ifndef WORKER_H
#define WORKER_H

#include <stack>
#include <thread>
#include <mutex>
#include <QDateTime>
#include <QUdpSocket>
#include <QHostAddress>

class Worker
{
public:
    Worker() = default;
    void start(int n);
    void stop();
private:
    void work();
private:
    std::thread thread_;
    bool running_;
    int n_;
};

#endif // WORKER_H
