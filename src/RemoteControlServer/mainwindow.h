#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>

#include "screenshot.h"
#include "serverthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void sendPasswordFromUISignal(const char* password);   // сигнал передачи пароля

public:
    MainWindow(QWidget *parent = nullptr);                 // конструктор
    ~MainWindow();                                         // деструктор

private slots:
    void on_actionExit_triggered();                        // выход из приложения
    void on_turn_on_pushButton_clicked();                  // включить сервер
    void on_turn_off_pushButton_clicked();                 // выключить сервер

public slots:
    void updateCursorSlot(int cursor_type);                // обновить рисунок курсора
    void showClientInfoSlot(QString s, const char* ip);    // показать информацию о подключенном клиенте
    void timeIsOverToConnectSlot();                        // время ожидания подключения вышло

private:
    Ui::MainWindow *ui;                                    // пользовательский интерфейс
    ServerThread serverThread;                             // рабочий поток для сервера
};
#endif // MAINWINDOW_H
