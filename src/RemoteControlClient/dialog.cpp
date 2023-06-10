#include "dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}

bool Dialog::isValidParametres() {
    setDataFromUI();
    if(validator.is_valid_IP(data.server_ip)) {
        return true;
    } else
        return false;
}

void Dialog::on_buttonBox_accepted()
{
    if(isValidParametres())
        QMessageBox::information(this, "Information", "Settings have been saved");
    else
        QMessageBox::warning(this, "Warning", "Data entered incorrectly");
}

void Dialog::on_buttonBox_rejected() {
    this->close();
}

void Dialog::setDataFromUI()
{
    data.server_ip = ui->IP_lineEdit->text();
    data.password = ui->password_lineEdit->text();
}

DataConnection Dialog::getData() const {
    return data;
}
