#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Соединение сигналов и слотов
    connect(&serverThread, &ServerThread::updateCursorSignal, this, &MainWindow::updateCursorSlot);
    connect(&serverThread, &ServerThread::sendClientInfoSignal, this, &MainWindow::showClientInfoSlot);
    connect(this, &MainWindow::sendPasswordFromUISignal, &serverThread, &ServerThread::receivePasswordFromUISlot);
    connect(&serverThread, &ServerThread::signalToTurnOff, this, &MainWindow::on_turn_off_pushButton_clicked);
    connect(&serverThread, &ServerThread::timeIsOverToConnectSignal, this, &MainWindow::timeIsOverToConnectSlot);
}

MainWindow::~MainWindow()
{
    serverThread.closeThread();
    serverThread.wait();
    serverThread.closeSockets();
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_turn_on_pushButton_clicked()
{
    // Установка всех признаков включенного сервера
    ui->turn_on_pushButton->setEnabled(false);
    this->statusBar()->showMessage("Is working...");
    this->setCursor(Qt::BusyCursor);

    // Проверка пароля
    if(ui->password_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Password field is empty");
        return;
    }

    // Отправка пароля в рабочий поток сервера
    emit sendPasswordFromUISignal(ui->password_lineEdit->text().toStdString().c_str());

    // Запуск потока сервера
    serverThread.start();
}


void MainWindow::on_turn_off_pushButton_clicked()
{
    // Установка всех признаков выключенного сервера
    this->statusBar()->showMessage("Server is off", STATUSBAR_DELAY);
    ui->turn_on_pushButton->setEnabled(true);
    ui->hostName->setText("...");
    ui->hostName->setAlignment(Qt::AlignCenter);
    ui->clientIP->setText("...");
    ui->clientIP->setAlignment(Qt::AlignCenter);

    // Смена рисунка курсора
    this->setCursor(Qt::ArrowCursor);

    // Закрытие потока
    serverThread.closeThread();
}


void MainWindow::updateCursorSlot(int cursor_type)
{
    switch(cursor_type)
    {
    case 0: this->setCursor(Qt::ArrowCursor); break; // курсор "Стрелка"
    case 1: this->setCursor(Qt::BusyCursor); break;  // курсор "Загрузка"
    }
}


void MainWindow::showClientInfoSlot(QString local_host_name, const char* ip)
{
    qDebug("Received hostname from client = %s", local_host_name.toStdString().c_str());
    qDebug("Received IP from client = %s\n", ip);
    ui->hostName->setText(local_host_name);
    ui->clientIP->setText(ip);
}


void MainWindow::timeIsOverToConnectSlot()
{
    QMessageBox::warning(this, "Warning", "Сonnection timed out");
    on_turn_off_pushButton_clicked();
    serverThread.closeThread();
    serverThread.wait();
}
