#include "admin.h"
#include "ui_admin.h"
#include"QMessageBox"
#include<QString>
#include"user.h"
#include<QTableWidgetItem>
#include<QInputDialog>
#include "interactionsystem.h"
#include<QFileDialog>

using namespace std;
Admin::Admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);
    userName = "salma";
    password = "123";
    ui->AdminChoice_stackWidget->setCurrentWidget(ui->choiceAdminPage);
QPixmap logo(":/img/logo1.png");

    ui->labelPhoto2->setPixmap(logo);
    ui->labelPhoto2->setScaledContents(true);
    ui->labelPhoto2_2->setPixmap(logo);
    ui->labelPhoto2_2->setScaledContents(true);

    ui->labelPhoto3->setPixmap(logo);
    ui->labelPhoto3->setScaledContents(true);

    ui->SETsuusphOTO->setPixmap(logo);
    ui->SETsuusphOTO->setScaledContents(true);
    ui->photoset->setPixmap(logo);
      ui->photoset->setScaledContents(true);
      ui->feesphoto->setPixmap(logo);
       ui->feesphoto->setScaledContents(true);
      ui->label_3->setPixmap(logo);
      ui->label_3->setScaledContents(true);
ui->label_12->setPixmap(logo);
      ui->label_12->setScaledContents(true);
ui->label_4->setPixmap(logo);
ui->label_4->setScaledContents(true);



}

void Admin::resetToLogin() {
    ui->Admin_stackWidget->setCurrentWidget(ui->ll);
    ui->adminUserName_line->clear();
    ui->AdminPass_line->clear();
}


void Admin::login( QString rawUsername,  QString rawPassword)
{

    if (rawUsername.isEmpty() || rawPassword.isEmpty()) {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Username or password cannot be empty.");
        msgBox.exec();
        return;
    }

    if (rawUsername == userName && rawPassword == password) {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Success");
        msgBox.setText("Login successful.");
        msgBox.exec();
        ui->Admin_stackWidget->setCurrentWidget(ui->AminMEnuPage);
    }
    else {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Failed");
        msgBox.setText("Login failed! Please check your credentials.");
        msgBox.exec();
    }
}

Admin::~Admin()
{
    delete ui;
}



void Admin::on_pushButton_2_clicked()
{


    ui->Admin_stackWidget->setCurrentWidget(ui->editUserrPage);
    ui->EditUser_stackWidget->setCurrentWidget(ui->chooseEdit);

}

void Admin::deleteUser(QString username)
{
    std::string userName = username.toStdString();

    auto it = User::users.find(userName);
    if (it == User::users.end()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("User not found!");
        msgBox.exec();
    }
    else {

        delete it->second;
        User::users.erase(it);
        User::donations.erase(userName);

        QMessageBox msgBox;
        msgBox.setWindowTitle("DELETED");
        msgBox.setText("User and donation record deleted successfully!");
        msgBox.exec();
    }
}


void Admin::ModifyBalance(QString userName,float amount,QString operation)
{
    std::string useN=userName.toStdString();



    if (!User::users.count(useN))
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("User not found!");
        msgBox.exec();
        return;

    }
    User* currentUser = User::users[useN];
    float bal = currentUser->get_balance();

    if (operation == "Add")
    {

        currentUser->set_balance(bal + amount);

        QMessageBox msgBox;
        msgBox.setWindowTitle("sucess");
        msgBox.setText("Balance modified successfully");
        QString noti="Your balance is Modified by the admin";
        currentUser->notifications.push(noti.toStdString());
        msgBox.exec();
    }

    else if (operation == "withdraw")
    {
        if (bal >= amount)
        {
            currentUser->set_balance(bal - amount);

            QMessageBox msgBox;
            msgBox.setWindowTitle("Success");
            msgBox.setText("Balance modified successfully");
            QString noti="Your balance is Modified by the admin";
            currentUser->notifications.push(noti.toStdString());
            msgBox.exec();

        }
        else{

        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Insufficient balance to withdraw!");
        msgBox.exec();}

    }
    else
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Invalid operation!");
        msgBox.exec();
    }

}
/*void Admin::addUser(User *user)
{
    std::string userNameStd = user->get_userName();
    if (User::users.count(userNameStd)) {


        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("User already exists");

        msgBox.exec();
    }
    else
    {
        User::users[userNameStd] = user;


        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("User added successfully");

        msgBox.exec();
    }
}*/
/*void Admin::addUser()
{
    QString username = ui->AdminADDuser_line->text();
    QString password = ui->passwordAdduser_line->text();
    QString Email = ui->Email_Adduser_line->text();

    string passwordStd = password.toStdString();

    QString usernamelower = username.toLower();
    QString hashingpassword = User::hashPassword(password);
    regex hasUppercase("[A-Z]");
    regex hasSpecialChar("[!@#$%^&*(),.?\":{}|<>]");

    if (username.isEmpty() || password.isEmpty() || Email.isEmpty()) {
        //QMessageBox::warning(this, "Warning", "Please fill in all fields!");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please fill in all fields!");

        msgBox.exec();
        return;
    }


    if (User::users.count(usernamelower.toStdString())) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("User already exists");

        msgBox.exec();
        return;
    }


    if (usernamelower.length() < 8) {
        //QMessageBox::critical(this, "Username Error", "Username must be at least 8 characters long.");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Username Error");
        msgBox.setText("Username must be at least 8 characters long.");

        msgBox.exec();
        return;
    }

    if (passwordStd.length() < 8) {
       // QMessageBox::critical(this, "Password Error", "Password must be at least 8 characters long.");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText("Password must be at least 8 characters long.");

        msgBox.exec();
        return;
    }


    if (!regex_search(passwordStd, hasUppercase)) {
       // QMessageBox::critical(this, "Password Error", "Password must contain at least one uppercase letter.");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText( "Password must contain at least one uppercase letter.");

        msgBox.exec();
        return;
    }


    if (!regex_search(passwordStd, hasSpecialChar)) {
       // QMessageBox::critical(this, "Password Error", "Password must contain at least one special character.");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText("Password must contain at least one special character.");

        msgBox.exec();
        return;
    }


    User* newUser = new User(usernamelower.toStdString(), hashingpassword.toStdString(),Email.toStdString());

    if (ui->donationRadio->isChecked())
    {
        QInputDialog inputDialog(this);
        inputDialog.setWindowTitle("Enter Image Path");
        inputDialog.setLabelText("Please enter the path to the image:");
        inputDialog.setInputMode(QInputDialog::TextInput);

        inputDialog.setStyleSheet(R"(
        QInputDialog {
            background: qlineargradient(
                x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 rgb(95, 48, 143),
                stop: 1 #D8A0E0
            );
            color: white;
            font: 700 15pt 'Segoe UI';
            border-radius: 40px;
            padding: 10px 25px;
        }
        QLabel {
            color: rgb(95, 48, 143);
            font: 700 13pt 'Segoe UI';
        }
        QLineEdit {
            background-color: white;
            color: black;
            font: 600 12pt 'Segoe UI';
            border-radius: 10px;
            padding: 4px;
        }
        QPushButton {
            background-color: white;
            color: rgb(95, 48, 143);
            border-radius: 15px;
            padding: 5px 15px;
            font: 600 11pt 'Segoe UI';
        }
        QPushButton:hover {
            background-color: #f0e6f6;
        }
    )");

        if (inputDialog.exec() == QDialog::Accepted) {
            QString imagePath = inputDialog.textValue();
            if (!imagePath.isEmpty()) {
                std::string usernamelowerStr = usernamelower.toStdString();
                std::string imagePathStr = imagePath.toStdString();

                User::donations[usernamelowerStr] = imagePathStr;

                QMessageBox msgBox;
                msgBox.setWindowTitle("Success");
                msgBox.setText("Donation User added successfully");
                msgBox.exec();

                for (const auto& it : User::donations)
                    qDebug() << QString::fromStdString(it.first) << " -> " << QString::fromStdString(it.second);
            } else {
                QMessageBox::warning(this, "Invalid Input", "No image path was entered.");
            }
        }
    }

    else if (ui->userradio->isChecked())
    {

        //QMessageBox::information(this, "Success", "User added successfully!");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("User added successfully");
    } else
    {
       // QMessageBox::warning(this, "Warning", "Please select a user type!");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please select a user type!");

        msgBox.exec();
        return;
    }



    ui->AdminADDuser_line->clear();
    ui->passwordAdduser_line->clear();
    ui->Email_Adduser_line->clear();
}*/

void Admin::addUser() {
    QString username = ui->AdminADDuser_line->text();
    QString password = ui->passwordAdduser_line->text();
    QString email = ui->Email_Adduser_line->text();

    QString usernamelower = username.toLower();
    std::string passwordStd = password.toStdString();
    QString hashedPassword = User::hashPassword(password);

    std::regex hasUppercase("[A-Z]");
    std::regex hasSpecialChar("[!@#$%^&*(),.?\":{}|<>]");

    // Validation
    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please fill in all fields!");

        msgBox.exec();
        return;
    }
    if (User::users.count(usernamelower.toStdString())) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("User already exists");

        msgBox.exec();
        return;
    }
    if (usernamelower.length() < 8) {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Username Error");
        msgBox.setText("Username must be at least 8 characters long.");
        return;
    }
    if (passwordStd.length() < 8) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText("Password must be at least 8 characters long.");
        return;
    }
    if (!std::regex_search(passwordStd, hasUppercase)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText( "Password must contain at least one uppercase letter.");

        return;
    }
    if (!std::regex_search(passwordStd, hasSpecialChar)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText("Password must contain at least one special character.");

        msgBox.exec();
        return;
    }


    User* newUser = new User(usernamelower.toStdString(), hashedPassword.toStdString(), email.toStdString());

    if (ui->donationRadio->isChecked()) {
        QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg)");
        if (!imagePath.isEmpty()) {
            QFile file(imagePath);
            if (file.open(QIODevice::ReadOnly)) {
                QByteArray imageData = file.readAll();
                QString base64Image = QString(imageData.toBase64());


                User::donations[usernamelower.toStdString()] = base64Image.toStdString();


                interactionsystem::saveDonationImagePath();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Success");
                msgBox.setText("Donation User added successfully");
                msgBox.exec();
            } else {
                QMessageBox::warning(this, "Error", "Failed to open image file.");
                return;
            }
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Invalid Input");
            msgBox.setText("No image was selected.");
            msgBox.exec();
            return;
        }
    }


     else if (ui->userradio->isChecked()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("User added successfully");
         msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please select a user type!");

        msgBox.exec();
        return;
    }

    // Save all users to JSON
    User::saveUsersToJson("C:/dss/Final_project11/Final_project/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/users.json");
}

void Admin::on_pushButton_8_clicked()
{
    ui->EditUser_stackWidget->setCurrentWidget(ui->ModifyPage);
}


void Admin::on_pushButton_7_clicked()
{
    ui->EditUser_stackWidget->setCurrentWidget(ui->changepassPage);
}


void Admin::on_pushButton_9_clicked()
{
    ui->EditUser_stackWidget->setCurrentWidget(ui->Set_susspendedPage);
}


void Admin::on_pushButton_12_clicked()
{

    ui->Admin_stackWidget->setCurrentWidget(ui->AminMEnuPage);

}


void Admin::on_pushButton_clicked()
{
    ui->AdminChoice_stackWidget->setCurrentWidget(ui->addUserPage);
}


void Admin::on_pushButton_3_clicked()
{
    ui->AdminChoice_stackWidget->setCurrentWidget(ui->deletUserPage);


}


void Admin::on_pushButton_5_clicked()
{
    ui->AdminChoice_stackWidget->setCurrentWidget(ui->viewTransactionsPage);

    viewalltransactions();
}


void Admin::on_pushButton_4_clicked()
{
    ui->AdminChoice_stackWidget->setCurrentWidget(ui->viewUsersPage);
    view_AlL_Users();

}


void Admin::on_pushButton_11_clicked()
{
    ui->AdminChoice_stackWidget->setCurrentWidget(ui->setFeesPage);
}


void Admin::on_pushButton_6_clicked()
{
 User::saveUsersToJson("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/users.json");
    interactionsystem::saveDonationImagePath();
    // resetToLogin();
    emit logoutClicked();
}
void Admin::view_AlL_Users()
{
    QWidget *contentWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);


    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(20);


    for (auto it : User::users) {
        User* user = it.second;

        QString userInfo = "Username: " + QString::fromStdString(it.first) + "\n"
                           + "Balance: " + QString::number(user->get_balance()) + "\n"
                           + "Is Suspended?: " + QString(user->get_suspended() ? "Yes" : "No");

        QFrame* userFrame = new QFrame;
        userFrame->setObjectName("userCard");
        QVBoxLayout* userLayout = new QVBoxLayout(userFrame);


        QLabel *userLabel = new QLabel(userInfo);
        userLabel->setObjectName("userInfoLabel");
        userLayout->addWidget(userLabel);


        QWidget* transactionsWidget = user->view_Transactions_History();
        userLayout->addWidget(transactionsWidget);


        layout->addWidget(userFrame);


        QFrame *line = new QFrame;
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(line);
    }

    contentWidget->setLayout(layout);
    ui->scrollusers->setWidget(contentWidget);
}



void Admin::on_pushButton_17_clicked()
{

    QString enteredUsername = ui->adminUserName_line->text();
    QString enteredPassword = ui->AdminPass_line->text();



    login(enteredUsername, enteredPassword);
}



void Admin::on_pushButton_15_clicked()
{
    addUser();


}
/*
bool Admin::deleteUser(string  username) {
    auto it = User::users.find(username);
    if (it != User::users.end()) {
        //  delete it->second;//3mlt error
        User::users.erase(it);
        return true;
    }
    return false;
}

*/
void Admin::on_pushButton_16_clicked()
{

    QString name=ui->deleteUser_line->text();
    if (name.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please enter a username to delete.");
        msgBox.exec();

        return;
    }
    deleteUser(name);
    /*
    QString qUsername = ui->deleteUser_line->text();
    std::string username = qUsername.toStdString();

    if (deleteUser(username)) {
        QMessageBox::information(this, "Success", "User has been deleted successfully!");
        view_AlL_Users();
    } else {
        QMessageBox::warning(this, "Error", "User not found!");
    }

*/
    ui->deleteUser_line->clear();

}


void Admin::on_Add_Radio_clicked()
{
    operation="Add";

}


void Admin::on_withdraw_Radio_clicked()
{

    operation="withdraw";


}


void Admin::on_ModifyButton_clicked()
{


    QString user=ui->ineditUser_line->text();

    QString amount=ui->amount_line->text();
    if (user.isEmpty() ||  amount.isEmpty() || operation.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please fill in all fields!");

        msgBox.exec();

        return;
    }
    float amoun=amount.toFloat();

    ModifyBalance( user, amoun, operation);
    ui->ineditUser_line->clear();
    ui->amount_line->clear();
    ui->Add_Radio->setChecked(false);
    ui->withdraw_Radio->setChecked(false);
    operation.clear();



}

void Admin::on_buttonforSetfees_clicked()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("DONE");
    msgBox.setText( "Modified successfully");

    msgBox.exec();
 //   QMessageBox::information(this, "DONE", "Modified successfully");
    qDebug()<<lowFeesRate;
    qDebug()<<highFeesRate;

}

void Admin::setFees(float  highFeesRate ,float lowFeesRate )
{
    this->lowFeesRate = lowFeesRate;
    this->highFeesRate = highFeesRate;
}


void Admin::on_highCombo_activated(int index)
{
    QString inp=ui->highCombo->currentText();
    float high=inp.toFloat();

    setFees(high,lowFeesRate);


    //ui->highCombo->setCurrentIndex(-1);
}


void Admin::on_lowCombo_activated(int index)
{
    QString inpu=ui->lowCombo->currentText();
    float low=inpu.toFloat();
    setFees(highFeesRate,low);
    //ui->lowCombo->setCurrentIndex(-1);
}



void Admin::changeUserPass(QString username, QString newPassword)
{
    std::string name=username.toStdString();


    regex hasUppercase("[A-Z]");
    regex hasSpecialChar("[!@#$%^&*(),.?\":{}|<>]");
    string passwordStd = newPassword.toStdString();
    QString hashingnewPassword = User::hashPassword(newPassword);

    if (!User::users.count(name))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText( "User Not found");

        msgBox.exec();

        return;
    }
    // Password length check
    if (passwordStd.length() < 8) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText( "Password must be at least 8 characters long.");

        msgBox.exec();

        return;
    }

    // Password must contain at least one uppercase letter
    if (!regex_search(passwordStd, hasUppercase)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText( "Password must contain at least one uppercase letter.");

        msgBox.exec();

        return;
    }

    // Password must contain at least one special character
    if (!regex_search(passwordStd, hasSpecialChar)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Password Error");
        msgBox.setText( "Password must contain at least one special character.");

        msgBox.exec();

        return;
    }
    else
    {

        User* user = User::users[name];
        qDebug ()<<"Pass before ubdate :" << user->get_password();
        user->setPassword(hashingnewPassword.toStdString());
        QMessageBox msgBox;
        msgBox.setWindowTitle("DONE");
        msgBox.setText( "password has been updated successfully");

        msgBox.exec();



        // qDebug() << "NEW pass:" << user->get_password();

    }
}

void Admin::on_pushButton_13_clicked()
{
    QString name=ui->NewuserPass_line->text();
    QString pass=ui->newPass_line->text();

    if(pass.isEmpty()|| name.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText( "please fill all fields");

        msgBox.exec();

        return;
    }

    changeUserPass( name, pass);
    ui->NewuserPass_line->clear();
    ui->newPass_line->clear();


}


void Admin::on_pushButton_10_clicked()
{
    ui->EditUser_stackWidget->setCurrentWidget(ui->reactivatePage);
}
void Admin::reactivateAcc(QString username) {
    std::string name=username.toStdString();

    if (!User::users.count(name))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText( "User not found");

        msgBox.exec();

        return;
    }


    else {
        User* user = User::users[name];

        if(user->get_suspended()==false)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Warning");
            msgBox.setText( "User is already Active");

            msgBox.exec();

            return;

        }

        user->set_suspended(false);

        QMessageBox msgBox;
        msgBox.setWindowTitle("DONE");
        msgBox.setText( "User is reactivated Successfully");

        msgBox.exec();
    }
}


void Admin::on_reactivateButton_clicked()
{
    QString name=ui->reactivate_Line->text();
    if(name.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText( "please fill all fields");

        msgBox.exec();

        return;
    }
    reactivateAcc(name);
    ui->reactivate_Line->clear();


}

void Admin::suspendAcc(QString username)
{
    std::string name=username.toStdString();

    if (!User::users.count(name))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText( "User not found");

        msgBox.exec();

        return;
    }

    else {
        User* user = User::users[name];
        if(user->get_suspended()==true)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Warning");
            msgBox.setText( "User is already suspended");

            msgBox.exec();

            return;

        }
        user->set_suspended(true);
        QMessageBox msgBox;
        msgBox.setWindowTitle("DONE");
        msgBox.setText( "User has been suspended");

        msgBox.exec();

    }
}

void Admin::on_susspendButton_clicked()
{
    QString name=ui->susspendLine->text();
    if(name.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("warning");
        msgBox.setText("please fill all fields" );

        msgBox.exec();


        return;
    }
    suspendAcc(name);
    ui->susspendLine->clear();
}



void Admin::viewalltransactions()
{
    stack<Transaction> tempStack = Transaction::alltransactions;

    QWidget *contentWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    while (!tempStack.empty())
    {
        Transaction transaction = tempStack.top();

        QString transactionInfo = "Sender: " + QString::fromStdString(transaction.getSender()) +
                                  "\nReceiver: " + QString::fromStdString(transaction.getReceiver()) +
                                  "\nAmount: " + QString::number(transaction.getamount()) +
                                  "\nDate: " + QString::fromStdString(transaction.date);

        // Create a label for each transaction
        QLabel *transactionLabel = new QLabel(transactionInfo);
        transactionLabel->setWordWrap(true);  // Allow the text to wrap if it's too long
        transactionLabel->setStyleSheet(
            "background-color: rgb(240, 240, 240);"  // Light gray background for each transaction
            "border: 1px solid rgb(95, 48, 143);"    // Purple border for the card
            "border-radius: 10px;"                    // Rounded corners for the card
            "padding: 15px;"                          // Padding inside the card for spacing
            "font: 600 14pt 'Segoe UI';"              // Font style
            "color: rgb(95, 48, 143);"                // Purple color for text
            "margin-bottom: 15px;"                    // Space between each transaction
            "box-shadow: 0 2px 6px rgba(0, 0, 0, 0.1);" // Subtle shadow for a raised effect
            );


        layout->addWidget(transactionLabel);


        QFrame *line = new QFrame;
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(line);

        tempStack.pop();  // Pop the transaction after displaying it
    }

    contentWidget->setLayout(layout);
    ui->scrolltrans->setWidget(contentWidget);
}

float Admin::AddFees(User* user, float amount)
{

    float feesRate;
    if (amount <= 1000)
    {
        feesRate = lowFeesRate;

    }
    else
    {
        feesRate = highFeesRate;
    }
    return (amount + amount*feesRate);
}

