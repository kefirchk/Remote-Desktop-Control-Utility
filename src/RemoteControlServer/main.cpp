/*
 *   REMOTE CONTROL SERVER
 *
 *   Created by Alexei Klimovich on 16.04.2023.
 *   Copyright © 2023 Alexei Klimovich. All rights reserved.
 *
 */

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Remote Control Server");
    w.show();
    return a.exec();
}
