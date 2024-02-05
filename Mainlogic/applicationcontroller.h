#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include<iostream>

#include "socket.h"
#include "worker.h"

class ApplicationController
{
public:
    ApplicationController(int port);
    void run();
private:
    bool started;
    std::vector<std::unique_ptr<Worker>> worker_;
    std::unique_ptr<Socket> socket_;
};

#endif // APPLICATIONCONTROLLER_H
