#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtNetwork>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public std::enable_shared_from_this<MainWindow>
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_start_clicked();

    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket_;
};

#endif // MAINWINDOW_H
