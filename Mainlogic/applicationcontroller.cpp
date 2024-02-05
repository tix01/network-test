#include "applicationcontroller.h"

//#define STOP_ONE_THREAD
#define STOP_ALL_THREADS

ApplicationController::ApplicationController(int port)
{
    socket_ = std::make_unique<Socket>(port);
}

void ApplicationController::run() {
    bool running = true;
    std::mutex m;
    try {
        while (running) {
            if (socket_->hasPendingDatagrams()) {
                auto [receivedText, t] = socket_->readDatagram();
                if (receivedText == "stop") {
 #ifndef STOP_ONE_THREAD
                    if (!worker_.empty()) {
                        auto& lastWorker = worker_.back();
                        lastWorker->stop();
                        lastWorker.reset();
                        worker_.pop_back();
                    }
#endif

#ifndef STOP_ALL_THREADS
                    for (auto& worker : worker_) {
                        worker->stop();
                        worker.reset();
                    }
                    worker_.clear();
                    running = false;
#endif

                    m.lock();
                    socket_->writeDatagram(receivedText, t,4321);
                    m.unlock();

                } else {
                    worker_.push_back(std::make_unique<Worker>());
                    int n = receivedText.toInt();
                    qDebug()<<n;
                    std::cout << n;
                    worker_[worker_.size()-1]->start(n);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
