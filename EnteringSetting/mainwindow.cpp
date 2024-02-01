#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket_ = new QUdpSocket(this);
}


MainWindow::~MainWindow()
{
    if (socket_) {
        socket_->close();
        delete socket_;
    }
    delete ui;
}
void MainWindow::on_start_clicked()
{
    QVariant text = ui->textSettings->text();

    if (text.toByteArray().size() > 65507) {
        qDebug() << "Too much data";
        return;
    }
    QString textStr = text.toString();

    QRegularExpression rx("^[0-9]+$");
    if (!rx.match(textStr).hasMatch()) {
        qDebug() << "Enter one number";
        return;
    }
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << textStr;
    stream << QDateTime::currentDateTime().toString(Qt::ISODate);

    if (socket_->writeDatagram(data, QHostAddress::LocalHost, 1234) == -1) {
        qDebug() << "Error sending settings";
    }
}

void MainWindow::on_stop_clicked()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    QString text = "stop";
    stream << text;
    stream << QDateTime::currentDateTime().toString(Qt::ISODate);
    if (socket_->writeDatagram(data, QHostAddress::LocalHost, 1234) == -1) {
        qDebug() << "Error sending signal about program completion";
    }
}





