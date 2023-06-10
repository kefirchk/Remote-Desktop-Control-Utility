#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "ui_dialog.h"
#include "validator.h"

struct DataConnection   // структура для установки соединения
{
    QString server_ip;  // IP сервера
    QString password;   // пароль на сервере
};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);  // конструктор
    ~Dialog();                                   // деструктор

    bool isValidParametres();                    // проверка валидности настроек
    DataConnection getData() const;              // получить структуру для создания соединения
    void setDataFromUI();                        // инициализировать структуру введенными данными с UI

private slots:
    void on_buttonBox_accepted();                // сохранить изменения
    void on_buttonBox_rejected();                // отменить измнения

private:
    Ui::Dialog *ui;                              // пользовательский интерфейс
    Validator validator;                         // валидатор настроек
    DataConnection data;                         // структура для создания сети
};

#endif // DIALOG_H
