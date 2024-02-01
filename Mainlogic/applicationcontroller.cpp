#include "applicationcontroller.h"

ApplicationController::ApplicationController(int port)
{
    worker_ = std::make_unique<Worker>();
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
                    worker_->stop();
                    m.lock();
                    socket_->writeDatagram(receivedText, t,4321);
                    m.unlock();
                    running = false;
                    started = false;
                } else if(!started){
                    started = true;
                    int n = receivedText.toInt();
                    std::cout << n;
                    worker_->start(n);
                    m.lock();
                    socket_->writeDatagram(QString::number(n), t,4321);
                    m.unlock();
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
