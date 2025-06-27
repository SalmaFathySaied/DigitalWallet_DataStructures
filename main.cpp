#include "mainwindow_1.h"
#include <iostream>
#include <string>
#include <QApplication>
#include "user.h"
#include "interactionsystem.h"
#include<QDir>
using namespace std;

void setMessageBoxStyle()
{
    qApp->setStyleSheet(
        "QMessageBox {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                stop: 0 rgb(95, 48, 143),"
        "                stop: 1 #D8A0E0);"
        "    color: white;"
        "    font: 700 15pt 'Segoe UI';"
        "    border: none;"
        "    border-radius: 40px;"
        "    padding: 10px 25px;"
        "}"
        "QLabel { color: white; font: 700 15pt 'Segoe UI'; }"
        "QPushButton {"
        "    background-color: white;"
        "    color: rgb(95, 48, 143);"
        "    font: 700 13pt 'Segoe UI';"
        "    border-radius: 20px;"
        "    padding: 5px 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #f0e6f5;"
        "}"
        );
}
int main(int argc, char *argv[])
{
    User::loadUsersFromJson("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/users.json");
    Transaction::loadtransactionsFromJson("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/alltransaction.json");
    interactionsystem::load_Donations_FromJson();
    qDebug() << "Current Path:" << QDir::currentPath();
    QString basePath = QCoreApplication::applicationDirPath();

    QApplication a(argc, argv);
       setMessageBoxStyle();
    MainWindow w;
    w.show();
    return a.exec();
}
