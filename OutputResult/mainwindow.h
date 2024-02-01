#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QDebug>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    struct Data {
        QString value;
        QString time;
    };
private:
    Data parseDatagram(QByteArray receivedData);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void receiveData();
    QByteArray readDatagram();


private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    QStandardItemModel* model;

};
#endif // MAINWINDOW_H
