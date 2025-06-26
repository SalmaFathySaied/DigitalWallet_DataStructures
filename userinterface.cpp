#include "userinterface.h"
#include "ui_userinterface.h"
#include "user.h"
#include "QMessageBox"
#include <QDebug>
#include <QFileDialog>

userinterface::userinterface(QWidget *parent)
    : QMainWindow(parent) ,
    ui(new Ui::userinterface) , userdoing(new interactionsystem(nullptr ,this)) , cadmin(new Admin(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(cadmin);
    ui->stackedWidget_2->setCurrentIndex(0);
    connect(userdoing , SIGNAL(BACK()) , this , SLOT(signalBACK()));
    connect(cadmin , SIGNAL(logoutClicked()) , this , SLOT(signalBACKFROMADMIN()));
    connect(ui->pushButton, &QPushButton::clicked, this, &userinterface::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &userinterface::on_pushButton_2_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &userinterface::on_pushButton_3_clicked);

    QPixmap photo(":/img/loginPhoto.png");
    ui->login_photo->setPixmap(photo);
    ui->login_photo->setScaledContents(true);
    QPixmap rphoto(":/img/register_photo.png");
    ui->labelPhoto->setPixmap(rphoto);
    ui->labelPhoto->setScaledContents(true);


}

userinterface::~userinterface()
{
    delete ui;
    delete userdoing;
    delete currentUser;
    delete cadmin;
}


void userinterface::on_pushButton_gotologin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void userinterface::on_pushButton_login_2_clicked()
{

    QString loginuser = ui->lineEdit_usernamelogin->text();
    QString loginpassword = ui->lineEdit_userpasswrodlogin->text();
    QString loginuserlower = loginuser.toLower();
    QString hashedInputPassword = User::hashPassword(loginpassword);


    if(loginuser == "admin" && loginpassword == "admin123")
    {
        QMessageBox::information(this , "Success" , "Welcome to admin Dashboard");

        ui->lineEdit_usernamelogin->clear();
        ui->lineEdit_userpasswrodlogin->clear();
        ui->stackedWidget->setCurrentWidget(cadmin);
        return;
    }

    if(loginuserlower.isEmpty() || loginpassword.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Please fill in all fields.");
        return;
    }

    if (User::users.count(loginuserlower.toStdString()) == 0)
    {
        QMessageBox::critical(this, "Login Failed", "User not found!");
        return;
    }


    if(User::users.count(loginuserlower.toStdString()) == 1)
    {
        if(User::users[loginuserlower.toStdString()]->get_password() != hashedInputPassword.toStdString()) {
            QMessageBox::critical(this , "Login Failed" ,"Wrong Password");
            return;
        }
        else if(User::users[loginuserlower.toStdString()]->get_suspended() == true)
        {
            QMessageBox::critical(this , "Login Failed" ,"Account is suspended");
            return;
        }
        else if(User::users[loginuserlower.toStdString()]->get_password() == hashedInputPassword.toStdString() && User::users[loginuserlower.toStdString()]->get_suspended() == false)
        {
            currentUser = User::users[loginuserlower.toStdString()];
            string currentusername = currentUser->get_userName();

            ui->lineEdit_usernamelogin->clear();
            ui->lineEdit_userpasswrodlogin->clear();
            QMessageBox::information(this , "Login Success" , "Welcome, " + loginuser + "!");

        }
    }

    if(currentUser == NULL)
    {
        return;
    }else
    {
        userdoing = new interactionsystem(currentUser, this);
        ui->stackedWidget->addWidget(userdoing);
        connect(userdoing , SIGNAL(BACK()) , this , SLOT(signalBACK()));
        ui->stackedWidget->setCurrentIndex(3);
    }
}


void userinterface::on_pushButton_register_clicked()
{

    QString username = ui->lineEdit_usernameregister->text().toLower();
    QString password = ui->lineEdit_userpasswordregister->text();
    QString email    = ui->lineEdit_useremailegister_2->text();


    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please fill in all fields.");
        return;
    }


    if (username.length() < 8) {
        QMessageBox::critical(this, "Username Error", "Username must be at least 8 characters long.");
        return;
    }
    if (password.length() < 8) {
        QMessageBox::critical(this, "Password Error", "Password must be at least 8 characters long.");
        return;
    }


    std::string pwdStr = password.toStdString();
    std::regex hasUppercase("[A-Z]");
    std::regex hasSpecialChar("[!@#$%^&*(),.?\":{}|<>]");
    if (!std::regex_search(pwdStr, hasUppercase)) {
        QMessageBox::critical(this, "Password Error", "Password must contain at least one uppercase letter.");
        return;
    }
    if (!std::regex_search(pwdStr, hasSpecialChar)) {
        QMessageBox::critical(this, "Password Error", "Password must contain at least one special character.");
        return;
    }

    if (!email.endsWith("@gmail.com")) {
        QMessageBox::warning(this, "Invalid Email", "Please enter a valid Gmail address.");
        return;
    }


    if (User::users.count(username.toStdString())) {
        QMessageBox::critical(this, "Error", "User already registered!");
        return;
    }

QString finalImagePath;


    if (tempImagePath.isEmpty()) {
        tempImagePath = ":/img/prof.jpg";
    }




    QString hashedPassword = User::hashPassword(password);
    User *u = new User(
        username.toStdString(),
        hashedPassword.toStdString(),
        email.toStdString(),
        this
        );



     u->setSelectedImagePath(tempImagePath);


    User::users[username.toStdString()] = u;


    currentUser = u;

    QMessageBox::information(this, "Success", "User registered successfully!");
    ui->lineEdit_usernameregister->clear();
    ui->lineEdit_userpasswordregister->clear();
    ui->lineEdit_useremailegister_2->clear();

    userdoing = new interactionsystem(currentUser, this);
    ui->stackedWidget->addWidget(userdoing);
    connect(userdoing, SIGNAL(BACK()), this, SLOT(signalBACK()));
    ui->stackedWidget->setCurrentIndex(3);




}


void userinterface::on_pushButton_Home_clicked()
{
    emit returnHome();
    ui->stackedWidget->setCurrentIndex(0);
}


void userinterface::signalBACK()
{
    if (userdoing)
    {
        ui->stackedWidget->removeWidget(userdoing);
        delete userdoing;
        userdoing = nullptr;
        currentUser = nullptr;
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void userinterface::signalBACKFROMADMIN()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void userinterface::on_pushButton_clicked()
{
    QString pythonPath = "C:/Python313/python.exe";
    QString scriptPath = "C:/dss/Final_project11/Final_project/send_reset_email.py";
    QString enteredUser = ui->lineEdit_enterededUser_2->text();
    QString enteredUserLower = enteredUser.toLower();

    if(User::users.count(enteredUserLower.toStdString()) != 0)
    {
        currentUser = User::users[enteredUserLower.toStdString()];
    }
    else
    {
        QMessageBox::information(this , "NO USER" , "No user Found");
        return;
    }

    if(enteredUser.isEmpty())
    {
        return;
    }

    if(currentUser == NULL)
    {
        QMessageBox::information(this , "NO USER" , "No user Found");
        return;
    }
    else
    {
        string currentUserEmail = currentUser->getEmail();
        QString CurrentUserEmailQS = QString::fromStdString(currentUserEmail);
        QStringList args;
        args << scriptPath << CurrentUserEmailQS << enteredUser;

        QProcess *process = new QProcess(this);
        process->start(pythonPath, args);

        connect(process, &QProcess::finished, this, [=](int, QProcess::ExitStatus) {
            QString otpFilePath = "C:/dss/Final_project11/Final_project/otp.txt";
            QFile file(otpFilePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                sentOtp = in.readLine();
                file.close();
                ui->stackedWidget_2->setCurrentIndex(2);
            } else {
                QMessageBox::warning(this, "Error", "Failed to read OTP file.");
            }
        });
    }

}



void userinterface::on_ForgetPasswordButton_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void userinterface::on_pushButton_continueForget_clicked()
{
    QString enteredOTP = ui->lineEdit_OTP->text();
    if (enteredOTP == sentOtp)
    {
        QMessageBox::information(this, "Success", "OTP Verified. You can now reset your password.");

        QString otpFilePath = "C:/Users/PC/Desktop/otp.txt";
        QFile::remove(otpFilePath);
        ui->stackedWidget_2->setCurrentIndex(3);
    }
    else
    {
        QMessageBox::warning(this, "Invalid", "Incorrect OTP. Please try again.");
    }
}

void userinterface::on_pushButton_2_clicked()
{
    QString newResetPassword = ui->lineEdit_resetPasswordR->text();
    if (newResetPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty.");
        return;
    }
    if (newResetPassword.length() < 8) {
        QMessageBox::critical(this, "Password Error", "Password must be at least 8 characters long.");
        return;
    }


    std::string pwdStr = newResetPassword.toStdString();
    std::regex hasUppercase("[A-Z]");
    std::regex hasSpecialChar("[!@#$%^&*(),.?\":{}|<>]");
    if (!std::regex_search(pwdStr, hasUppercase)) {
        QMessageBox::critical(this, "Password Error", "Password must contain at least one uppercase letter.");
        return;
    }
    if (!std::regex_search(pwdStr, hasSpecialChar)) {
        QMessageBox::critical(this, "Password Error", "Password must contain at least one special character.");
        return;
    }
    QString newResetPasswordHashing = User::hashPassword(newResetPassword);
    currentUser->setPassword(newResetPasswordHashing.toStdString());
    ui->stackedWidget_2->setCurrentIndex(0);
    currentUser = NULL;
}


void userinterface::on_pushButton_3_clicked()
{
    // 1) open file dialog
    QString path = QFileDialog::getOpenFileName(
        this,
        "Select Profile Image",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)"
        );

    if (path.isEmpty()) {
        // user cancelled
        return;
    }

    // 2) preview it
    /*
    QPixmap pix(path);
    if (!pix.isNull()) {
        ui->image_label->setPixmap(
            pix.scaled(ui->image_label->size(),
                       Qt::KeepAspectRatio,
                       Qt::SmoothTransformation)
            );
    }
*/
    // 3) store it for later
    tempImagePath = path;
}



