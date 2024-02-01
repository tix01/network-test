#include <iostream>
#include "applicationcontroller.h"



int main() {
    int port = 1234;
    ApplicationController app(port);
    app.run();
    return 0;
}
