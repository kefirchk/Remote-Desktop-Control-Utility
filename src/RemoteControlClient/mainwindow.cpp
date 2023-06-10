#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings.setDataFromUI();  // получение настроек с UI

    // Соединение сигналов и слотов
    connect(this, &MainWindow::sendSettingsFromUISignal, &clientThread, &ClientThread::receiveSettingsFromUISlot);
    connect(&clientThread, &ClientThread::showPasswordStatusSignal, this, &MainWindow::showPasswordStatusSlot);
    connect(&clientThread, &ClientThread::signalToDisconnect, this, &MainWindow::on_actionDisconnect_from_the_server_triggered);
    connect(&clientThread, &ClientThread::screenshotReady, this, &MainWindow::updateScreenshot);
    connect(&clientThread, &ClientThread::connectFailedSignal, this, &MainWindow::connectFailedSlot);
    connect(this, &MainWindow::mouseEventToClientThreadSignal, &clientThread, &ClientThread::getMouseEventFromWindowSlot);
    connect(this, &MainWindow::keyIsPressed, &clientThread, &ClientThread::getKeyEventFromWindowSlot);
}

MainWindow::~MainWindow() {
    clientThread.closeThread();
    clientThread.wait();
    delete ui;
}

void MainWindow::on_actionExit_triggered() {
    this->close();
}

void MainWindow::on_actionSettings_triggered() {
    settings.setWindowTitle("Settings");
    settings.show();
    settings.exec();
}

void MainWindow::updateScreenshot(QImage screenshotImage) {
    QPixmap screenshot = QPixmap::fromImage(screenshotImage);
    ui->remoteScreen_label->setScaledContents(true);
    QPixmap scaledPixmap = screenshot.scaled(ui->remoteScreen_label->size(), Qt::KeepAspectRatio);
    ui->remoteScreen_label->setPixmap(scaledPixmap);
}

void MainWindow::on_actionConnect_to_server_triggered()
{
    //Проверка валидности настроек для подключения
    if(settings.isValidParametres() == false)
    {
        QMessageBox::warning(this, "Warning", "Incorrect settings data entered");
        return;
    }
    if(settings.getData().password.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Password field is empty");
        return;
    }

    // Включение клиента
    ui->actionConnect_to_server->setEnabled(false);
    ui->statusbar->showMessage("Is working...");

    // Отправка настроек для связи
    emit sendSettingsFromUISignal(settings.getData());

    // Запуск потока для клиента
    clientThread.start();

    // Спрятать лишние менюшки
    this->setWindowState(Qt::WindowFullScreen);
    this->menuWidget()->setVisible(false);
    this->menuBar()->setVisible(false);
}


void MainWindow::on_actionDisconnect_from_the_server_triggered() {
    // Установка всех признаков отсоединенного клиента от сервера
    ui->actionConnect_to_server->setEnabled(true);
    ui->remoteScreen_label->clear();
    ui->remoteScreen_label->setText("(Here is a remote screen)");
    ui->remoteScreen_label->setStyleSheet("font: italic");
    ui->remoteScreen_label->setAlignment(Qt::AlignCenter);
    this->statusBar()->showMessage("Сonnection interrupted", STATUSBAR_DELAY);

    // Закрытие потока
    clientThread.closeThread();
    clientThread.wait();

    // Изменение размеров окна
    this->setWindowState(Qt::WindowMaximized);
    this->menuBar()->setVisible(true);
    this->menuWidget()->setVisible(true);
    this->resize(800, 600);
}

void MainWindow::showPasswordStatusSlot(int status)
{
    if(status == 1) {
        QMessageBox::information(this, "Success", "You are connected successfully.\nPress F12 to show the menu.");
    } else {
        QMessageBox::warning(this, "Failure", "Wrong password");
        on_actionDisconnect_from_the_server_triggered();
    }
}

void MainWindow::connectFailedSlot() {
    QMessageBox::critical(this, "Error", "Connect failed\nTry again");
    on_actionDisconnect_from_the_server_triggered();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyText = event->text();
    qDebug() << "\nKEY = " << keyText << " qt_key_code=" <<  event->key() << " native_key_code=" << event->nativeVirtualKey() << "\n";
    emit keyIsPressed(Keyboard::IS_PRESSED, event->nativeVirtualKey());

    // Обработка символа, связанного с нажатой клавишей
    if (event->key() == Qt::Key_F12) {
        if(this->windowState() == Qt::WindowFullScreen)
        {
            this->setWindowState(Qt::WindowMaximized);
            this->menuBar()->setVisible(true);
            this->menuWidget()->setVisible(true);
            this->resize(800, 600);
        } else {
            this->setWindowState(Qt::WindowFullScreen);
            this->menuWidget()->setVisible(false);
            this->menuBar()->setVisible(false);
        }
    } else
        QWidget::keyPressEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "==============LEFT PRESS===============";
        emit mouseEventToClientThreadSignal(Mouse::LEFT_PRESS);
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "==============RIGHT PRESS==============";
        emit mouseEventToClientThreadSignal(Mouse::RIGHT_PRESS);
    }
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    qDebug() << "================RELEASE================";
    emit mouseEventToClientThreadSignal(Mouse::RELEASE);
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    qDebug() << "=================MOVE==================";
    emit mouseEventToClientThreadSignal(Mouse::MOVE);
    event->accept();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event) {
    qDebug() << "==============DOUBLECLICK==============";
    emit mouseEventToClientThreadSignal(Mouse::DOUBLECLICK);
    event->accept();
}
