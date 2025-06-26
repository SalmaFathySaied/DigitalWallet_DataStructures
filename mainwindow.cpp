#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , userRegorLogin(new userinterface(this))
{
    ui->setupUi(this);
    this->showMaximized();
    ui->stackedWidget1->setCurrentWidget(0);
    ui->stackedWidget1->insertWidget(1 , userRegorLogin);
    connect(userRegorLogin , SIGNAL(returnHome()) , this , SLOT(ReturnHome()));
    ui->stackedWidget1->setStyleSheet("QStackedWidget { background-image: url(:/img/pp.jpg); background-repeat: no-repeat; background-position: center; }");

    /*
    ui->StartPage->setStyleSheet(
        "background-image: url(\"C:/Users/acer/Documents/FARRRR/Final_project11/Final_project/pp.jpg\");"

        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-size: cover;"
        );*/
   // QPixmap logo(":/img/logo1.png");
   // this->setStyleSheet("QWidget { background-image: url(:C:/Users/acer/Documents/FARRRR/Final_project11/Final_project/pp.jpg); }");

    //ui->pfpLabel->setPixmap(logo);
   // ui->pfpLabel->setScaledContents(true);


}
MainWindow::~MainWindow()
{
    delete ui;
    delete userRegorLogin;

}



void MainWindow::on_GetStarted_clicked()
{

    ui->stackedWidget1->setCurrentIndex(1);
}

void MainWindow::ReturnHome()
{
    ui->stackedWidget1->setCurrentIndex(0);
}




