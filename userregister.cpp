// #include "userregister.h"
// #include "ui_userregister.h"
// #include <QMessageBox>
// #include <QPushButton>
// #include "user.h"

// userregister::userregister(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::userregister)
// {
//     ui->setupUi(this);
// }

// userregister::~userregister()
// {
//     delete ui;
// }




// void userregister::on_RegisterButton_clicked()
// {
//     QString username = ui->lineEdit->text();
//     QString password = ui->lineEdit_2->text();

//     QString usernamelower = username.toLower();

//     if(usernamelower.isEmpty() || password.isEmpty())
//     {
//         QMessageBox::critical(this , "Error" , "Please fill in all fields.");
//         return;
//     }

//     if(User::users.count(usernamelower.toLower().toStdString()) != 0)
//     {
//         QMessageBox::critical(this , "Error" , "User already registered!");
//     }
//     else
//     {
//         User::users[usernamelower.toStdString()] = new User(usernamelower.toStdString() , password.toStdString() , this);
//         QMessageBox::information(this , "Success" , "User registered successfully!");
//     }
// }

