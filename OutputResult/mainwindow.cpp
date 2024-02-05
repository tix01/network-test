#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    model = new QStandardItemModel(this);
    ui->listView->setModel(model);

    connect(socket, &QUdpSocket::readyRead, this, &MainWindow::receiveData);

    socket->bind(4321);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveData() {
    while (socket->hasPendingDatagrams()) {
        QByteArray receivedData = readDatagram();
        Data data = parseDatagram(receivedData);
        QStandardItem *item;
        qDebug() << data.value << data.time;
        item = new QStandardItem(data.value + " " + data.time);
        model->appendRow(item);

    }
}

QByteArray MainWindow::readDatagram() {
    QByteArray receivedData;
    receivedData.resize(socket->pendingDatagramSize());
    socket->readDatagram(receivedData.data(), receivedData.size());
    return receivedData;
}

MainWindow::Data MainWindow::parseDatagram(QByteArray receivedData) {
    QDataStream inStream(receivedData);
    Data data;
    inStream >> data.value >> data.time;
    return data;
}
