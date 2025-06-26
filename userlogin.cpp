// #include "userlogin.h"
// #include "ui_userlogin.h"
// #include <QMessageBox>
// #include "user.h"
// #include "interactionsystem.h"

// userlogin::userlogin(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::userlogin)
// {
//     ui->setupUi(this);
// }

// userlogin::~userlogin()
// {
//     delete ui;
// }

// User * userlogin::on_LoginButton_clicked()
// {

//     User * current = NULL;
//     QString loginuser = ui->login_username->text();
//     QString loginpassword = ui->login_password->text();
//     QString loginuserlower = loginuser.toLower();

//     if(loginuserlower.isEmpty() || loginpassword.isEmpty())
//     {
//         QMessageBox::critical(this, "Error", "Please fill in all fields.");
//         return 0;
//     }

//     if (User::users.count(loginuserlower.toStdString()) == 0)
//     {
//         QMessageBox::critical(this, "Login Failed", "User not found!");
//         return 0;
//     }


//     if(User::users.count(loginuserlower.toStdString()) == 1)
//     {
//         if(User::users[loginuserlower.toStdString()]->get_password() != loginpassword.toStdString())
//         {
//             QMessageBox::critical(this , "Login Failed" ,"Wrong Password");
//             return 0;
//         }
//         else if(User::users[loginuserlower.toStdString()]->get_suspended() == true)
//         {
//             QMessageBox::critical(this , "Login Failed" ,"Account is suspended");
//             return 0;
//         }
//         else if(User::users[loginuserlower.toStdString()]->get_password() == loginpassword.toStdString() && User::users[loginuserlower.toStdString()]->get_suspended() == false)
//         {
//             current = User::users[loginuserlower.toStdString()];
//             string currentusername = current->get_userName();
//             QMessageBox::information(this , "Login Success" , "Welcome, " + loginuser + "!");

//         }
//     }

//     if(current == NULL)
//     {
//         return 0 ;
//     }
//     else
//     {
//         interactionsystem * interface = new interactionsystem(current);
//         interface->show();
//         this->hide();
//     }
//     return current;

// }

