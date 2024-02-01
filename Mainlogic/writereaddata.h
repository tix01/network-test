#ifndef WRITEREADDATA_H
#define WRITEREADDATA_H

#include<stack>
#include<vector>
#include<QtNetwork>
#include<iostream>

class WriteReadData
{
public:
    WriteReadData();
    void writeData();
    void readData();
private:
    QUdpSocket* socket;//умный указатель
    std::stack<int,std::vector<int>> data;
    int N;
};

#endif // WRITEREADDATA_H
