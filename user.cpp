#include "user.h"
#include"admin.h"
#include"transaction.h"
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLayout>
#include <QLabel>
#include "interactionsystem.h"
#include <QPushButton>
#include<stack>
unordered_map<string, User*> User::users;
unordered_map<string,string> User::donations;
stack <string>notifications;
// extern unordered_map<string , User *> users;

User::User(string userName, string password, string email , QWidget* parent)
{

    this->userName = userName;
    this->password = password;
    this->Email = email;
    balance = 0;
    isSuspended = false;
    this->parentWidget = parent;
     users[userName]=this;
}

string User::get_userName()
{
    return userName;
}
string User::get_password()
{
    return password;
}

string User::getEmail()
{
    return Email;
}

void User::setEmail(string email)
{
    Email = email;
}

void User::setUsername(string USERNAME)
{
    userName = USERNAME;
}
float User::get_balance()
{
    return balance;
}
bool User::get_suspended()
{
    return isSuspended;
}

void User::set_balance(float amount)
{
    balance = amount;
}


void User::set_suspended(bool status) {
    isSuspended = status;
}



void User::setSelectedImagePath( QString& path) {
    selectedImagePath = path;
}

QString User::getSelectedImagePath()
{
    return selectedImagePath;
}

// void User::registerUser(string username, string password)
// {
//     if (users.count(username) == 0)
//     {
//         users[username] = new User(username, password);
//         cout << "User registered successfully!" << endl;
//         return;
//     }
//     else
//     {
//         cout << "User already registered" << endl;
//     }

// }

// void User::login(string username, string password)
// {
//     User * currentUser = nullptr;
//     if (users.count(username) == 0)
//     {
//         cout << "User not found!" << endl;
//         return;
//     }
//     else
//     {
//         if (users[username]->get_password() != password)
//         {
//             cout << "Incorrect password!" << endl;
//             return;
//         }
//         else if (users[username]->get_suspended() == true)
//         {
//             cout << "Account is suspended!" << endl;
//             return;
//         }
//         else if (users[username]->get_suspended() == false && users[username]->get_password() == password)
//         {
//             cout << "Login successful!" << endl;
//             currentUser = users[username];
//         }
//     }


//     if(currentUser == nullptr)
//     {
//         return;
//     }
//     else
//     {

//     }

// }


/*void User::requestMoney(string receiverName, float amount)
{
    if (validUser(receiverName))
    {
        Transaction request(userName, receiverName, amount);
        User* Receiver = User::users[receiverName];
        Receiver->requests.push(request);
        QMessageBox::information(parentWidget, "Success", "Request Sent");
    }
    else
    {
        QMessageBox::critical(parentWidget, "Error", "User Not Found!");
    }
}*/


void User::requestMoney(string receiverName, float amount)
{


    if (validUser(receiverName))
    {
        Transaction request(userName, receiverName, amount);
        User* Receiver = User::users[receiverName];
        Receiver->requests.push(request);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("Request Sent");

         QString mamount = QString::number(amount);
        QString qReciverName = QString::fromStdString(receiverName);
        QString usNotification="You have sent a request for "+mamount + " EGP " + " to " +qReciverName;
        this->notifications.push(usNotification.toStdString());



        QString qSender = QString::fromStdString(this->get_userName());
        QString notification = "You have Recived a Request from : " +qSender +" for " + mamount+ " EGP ";


       Receiver->notifications.push(notification.toStdString());




        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("User Not Found!");

        msgBox.exec();
    }
}



void User::viewRequests()
{
    queue<Transaction>temp;
    while (!requests.empty())
    {

        Transaction currentRequest = requests.front(); requests.pop();
        cout << "[1] Accept" << endl;
        cout << "[2] Decline" << endl;
        cout << "[3] Skip" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            if (balance >= currentRequest.getamount())
            {
                // Send Money();
            }
            else
            {
                cout << "Insufficent Bakance \n Request Decilned" << endl;
            }
        }
        else if (choice == 2)
        {

            continue;
        }
        else if (choice == 3)
        {
            temp.push(currentRequest);

        }
        else
        {
            cout << "Invalid Choice" <<endl;
        }
    }
    while (!temp.empty())
    {
        requests.push(temp.front());
        temp.pop();
    }

}




void User::popFrontRequest()
{
    if (!requests.empty()) {
    requests.pop();
}
}

void User::skipFrontRequest() {
    if (!requests.empty()) {
        Transaction front = requests.front();
        requests.pop();
        requests.push(front);  // Move the request to the back of the queue
    }
}

Transaction User::getFrontRequest() {
    if (!requests.empty()) {
        return requests.front();
    } else {
        throw std::runtime_error("No requests available.");
    }
}

bool User::hasRequests() {
    return !requests.empty();
}




QString User::viewBalance(float multiplier , string currency) {

    QString msg = " The User Current Balance is: " + QString::number(balance / multiplier, 'f', 2) + " " + QString::fromStdString(currency);

    return msg;
}



void User::sendMoney(string receiverUserName , float qamount) {


    if (!validUser(receiverUserName)) {
        //QMessageBox::critical(parentWidget, "ATTENTION", "There Is No Account With This Name");
                QMessageBox msgBox(parentWidget);
                msgBox.setText("There Is No Account With This Name");
                msgBox.setWindowTitle("ATTENTION");
                 msgBox.exec();

        qDebug() << "There Is No Account With This Name \n";
        return;
    }

    if (qamount > this->balance) {


        QMessageBox msgBox(parentWidget);
        msgBox.setText("No Enough Charge To Complete The proccess");
        msgBox.setWindowTitle("ATTENTION");



        msgBox.exec();



        qDebug()<< "No Enough Charge To Complete The proccess \n";
        return;
    }

    if(userName == receiverUserName)
    {

        QMessageBox msgBox(parentWidget);
        msgBox.setText("Can't Send Money to Yourself!");
        msgBox.setWindowTitle("ATTENTION");



        msgBox.exec();




        return;
    }
    if (this->isSuspended == true) {
        QMessageBox msgBox(parentWidget);
        msgBox.setText("Failed");
        msgBox.setWindowTitle("Sorry Your Account Is Suspended");
        msgBox.exec();
        return;
    }
    else if (users[receiverUserName]->isSuspended == true) {
        QMessageBox msgBox(parentWidget);
        msgBox.setText("Done Successfully");
        msgBox.setWindowTitle("Sorry The Receiver Account Is Suspended");
        msgBox.exec();
        return;
    }

    Admin admin;
    float feesed= admin.AddFees(this, qamount);
    balance = balance - feesed;
   users[receiverUserName]->balance += qamount;

     //this->set_balance(this->get_balance() - feesed);

  // User::users[receiverUserName]->set_balance(User::users[receiverUserName]->get_balance() + qamount);
    //QMessageBox::about(parentWidget, "successfull transaction", "Done Successfully");
    QMessageBox msgBox(parentWidget);
    msgBox.setText("Done Successfully");
    msgBox.setWindowTitle("successfull transaction");
    msgBox.exec();
    qDebug()<< "Done Successfully \n";
    QString mamount = QString::number(qamount);
    QString qReceiverName = QString::fromStdString(receiverUserName);
    QString notification = "You have sent " + mamount + " to " + qReceiverName;
    this->notifications.push(notification.toStdString());
    QString qSenderName = QString::fromStdString(this->get_userName());
    QString receiverNotification = " You have received " + mamount + " EGP " + " from " + qSenderName;
    users[receiverUserName]->notifications.push(receiverNotification.toStdString());
    Transaction trans(userName, receiverUserName, qamount);
    transactions.push(trans);
    Transaction transReceiver(userName , receiverUserName , qamount);
    users[receiverUserName]->transactions.push(transReceiver);
    Transaction::alltransactions.push(trans);
    qDebug()<<Transaction::alltransactions.size();
    viewBalance(1 , "EGP");


    }



QWidget* User::view_Transactions_History()
{
    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(container);

    stack<Transaction> tempStack = transactions;

    if (!tempStack.empty()) {
        while (!tempStack.empty()) {
            Transaction t = tempStack.top();
            tempStack.pop();

            QString transactionDetails =
                "Sender: " + QString::fromStdString(t.getSender()) + "\n" +
                "Receiver: " + QString::fromStdString(t.getReceiver()) + "\n" +
                "Amount: " + QString::number(t.getamount()) + "\n" +
                "Date: " + QString::fromStdString(t.date);

            QLabel* label = new QLabel(transactionDetails);
            label->setStyleSheet(R"(
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 rgb(95, 48, 143),
                    stop: 1 #D8A0E0
                );
                color: white;
                font: 700 15pt "Segoe UI";
                border: none;
                border-radius: 40px;
                padding: 10px 25px;
            )");

            label->setWordWrap(true);
            layout->addWidget(label);
        }
    } else {
        QLabel* label = new QLabel("No transactions found.");

        layout->addWidget(label);
    }

    container->setLayout(layout);
    return container;
}


bool User::validUser(string checkUser)
{
    if (User::users.count(checkUser) == 0)
    {
        return false;
    }

    return true;
}

void User::setPassword(string pass)
{
    password = pass;
}


bool User::loginconstraints(string checkingpass)
{

    regex hasUppercase("[A-Z]");
    regex hasSpecialChar("[!@#$%^&*(),.?\":{}|<>]");
    if(password == checkingpass)
    {
        QMessageBox::critical(parentWidget, "Password Error", "Password can't be as already used.");
        return false;
    }

    if (checkingpass.length() < 8) {
            QMessageBox::critical(parentWidget, "Password Error", "Password must be at least 8 characters long.");
            return false;
        }

    if (!regex_search(checkingpass, hasUppercase)) {
        QMessageBox::critical(parentWidget, "Password Error", "Password must contain at least one uppercase letter.");
        return false;
    }

    if (!regex_search(checkingpass, hasSpecialChar)) {
        QMessageBox::critical(parentWidget, "Password Error", "Password must contain at least one special character.");
        return false;
    }

    return true;
}

bool User::currentpasscorrect(string passbeforesave)
{
    if(password != passbeforesave)
    {
        QMessageBox::critical(parentWidget , "Error" , "Wrong Password");
        return false;
    }

    return true;
}

/*
void User::loadUsersFromJson(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray usersArray = doc.array();

    for (const QJsonValue& val : usersArray) {
        QJsonObject obj = val.toObject();
        string userName = obj["userName"].toString().toStdString();
        string password = obj["password"].toString().toStdString();
        string email = obj["email"].toString().toStdString();  // Load email
        float balance = obj["balance"].toDouble();
        bool suspended = obj["isSuspended"].toBool();
        QString picPath = obj["profilePicturePath"].toString();
       // User* u = new User(userName, password, email, nullptr, picPath);

        // Pass the email when creating the User object
        User* u = new User(userName, password, email);
        u->balance = balance;
        u->isSuspended = suspended;
        u->setProfileImageBase64(picPath.toStdString());
        u->transactions = deserializeStack(obj["transactions"].toArray());
        u->requests = deserializeQueue(obj["requests"].toArray());


        users[userName] = u;
    }
    file.close();
}



void User::saveUsersToJson(const QString& filePath) {
    QJsonArray usersArray;
    for (auto& pair : users) {
        User* user = pair.second;
        QJsonObject userObj;

        // Add user details to the JSON object
        userObj["userName"] = QString::fromStdString(user->userName);
        userObj["password"] = QString::fromStdString(user->password);
        userObj["email"] = QString::fromStdString(user->Email);
        userObj["balance"] = user->balance;
        userObj["isSuspended"] = user->isSuspended;
        QString base64Image = QString::fromStdString(user->getProfileImageBase64());
        if (!base64Image.isEmpty()) {
            userObj["profilePictureBase64"] = base64Image;
        } else {

            userObj["profilePictureBase64"] = "";
        }

        userObj["transactions"] = user->serializeStack(user->transactions);
        userObj["requests"] = user->serializeQueue(user->requests);

        usersArray.append(userObj);
    }

    QJsonDocument doc(usersArray);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}
*/
void User::loadUsersFromJson(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray usersArray = doc.array();

    for (const QJsonValue& val : usersArray) {
        QJsonObject obj = val.toObject();
        string userName = obj["userName"].toString().toStdString();
        string password = obj["password"].toString().toStdString();
        string email = obj["email"].toString().toStdString();  // Load email
        float balance = obj["balance"].toDouble();
        bool suspended = obj["isSuspended"].toBool();
        QString picPath = obj["profilePicture"].toString();  // Load Base64 image string

        // Create User object
        User* u = new User(userName, password, email);
        u->balance = balance;
        u->isSuspended = suspended;

        // Set the Base64 image if available
        if (!picPath.isEmpty()) {
            u->setSelectedImagePath(picPath);
        }

        u->transactions = deserializeStack(obj["transactions"].toArray());

        u->requests = deserializeQueue(obj["requests"].toArray());
        // u->notifications = deserializeStack(obj[""].toArray());
        u->notifications = deserializeStacknotification(obj["notifications"].toArray());


        // Add user to users map
        users[userName] = u;
    }

    file.close();
}
/*
void virewNotifications()
{
    std::satck<std::string> temp=notifications;
    while(!temp.empty())
    {
        string to=temp.top();
        cout<<"to"<<endl;
        temp.pop();
    }


}
*/
void User::saveUsersToJson(const QString& filePath) {
    QJsonArray usersArray;
    for (auto& pair : users) {
        User* user = pair.second;
        QJsonObject userObj;

        // Add user details to the JSON object
        userObj["userName"] = QString::fromStdString(user->userName);
        userObj["password"] = QString::fromStdString(user->password);
        userObj["email"] = QString::fromStdString(user->Email);
        userObj["balance"] = user->balance;
        userObj["isSuspended"] = user->isSuspended;
        userObj["profilePicture"] = user->getSelectedImagePath();

        userObj["transactions"] = user->serializeStack(user->transactions);
        userObj["requests"] = user->serializeQueue(user->requests);
        userObj["notifications"] = user->serializeStacknotification(user->notifications);
        usersArray.append(userObj);
    }

    QJsonDocument doc(usersArray);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}


QJsonArray User::serializeStack(const stack<Transaction>& trans) const {
    QJsonArray array;
    stack<Transaction> temp = trans;
    while (!temp.empty()) {
        array.append(temp.top().toJson());
        temp.pop();
    }
    return array;
}

QJsonArray User::serializeQueue(const queue<Transaction>& reqs) const {
    QJsonArray array;
    queue<Transaction> temp = reqs;
    while (!temp.empty()) {
        array.append(temp.front().toJson());
        temp.pop();
    }
    return array;
}

stack<Transaction> User::deserializeStack(const QJsonArray& array) {
    vector<Transaction> vec;
    for (const auto& val : array) {
        vec.push_back(Transaction::fromJson(val.toObject()));
    }
    stack<Transaction> s;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        s.push(*it);
    }
    return s;
}

queue<Transaction> User::deserializeQueue(const QJsonArray& array) {
    queue<Transaction> q;
    for (const auto& val : array) {
        q.push(Transaction::fromJson(val.toObject()));
    }
    return q;
}


QString User::hashPassword(QString password) {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

bool User:: editusername(QString newusername){
    if (users.count(newusername.toStdString())==1 )
    {    QMessageBox successBox;
        successBox.setWindowTitle("failed");
        successBox.setText("Username already exist");
        successBox.exec();

        return false;
    }

    else{
    QMessageBox confirmBox;
    confirmBox.setWindowTitle("Confirm");
    confirmBox.setText("Are you sure you want to change your username to " + newusername + "?");
    confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);


    if (confirmBox.exec() == QMessageBox::Yes) {
        users.erase(get_userName());
        setUsername(newusername.toStdString());
        users[newusername.toStdString()] = this;
        return true;
    }
    else {

        QMessageBox failbox;
        failbox.setWindowTitle("failed");
        failbox.setText("Username not changed ");
        failbox.exec();
         return false;

    }
    }
}
bool User:: checkcurrentpassword(QString passwordbeforenext){
    QString passwordbeforenexthashing = hashPassword(passwordbeforenext);
    string passwordbeforenexthashingbeforeconvertion = passwordbeforenexthashing.toStdString();
    bool answer;
    answer=currentpasscorrect(passwordbeforenexthashingbeforeconvertion);
    return answer;
}
bool User::editpassword(QString newpassword){
    string newpasswordconverted = newpassword.toStdString();
    QString hashingnewpassord = hashPassword(newpassword);
    string newpasswordconvertedhasing = hashingnewpassord.toStdString();



    if (loginconstraints(newpasswordconverted))
    {
        QMessageBox confirmBox;
        confirmBox.setWindowTitle("Confirm");
        confirmBox.setText("Are you sure you want to change your password to " + newpassword + " ?");
        confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);


        if (confirmBox.exec() == QMessageBox::Yes) {
            setPassword(newpasswordconvertedhasing);

            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}
QJsonArray User::serializeStacknotification(const stack<string>& notifications) {
    QJsonArray array;
    stack<string> temp = notifications;
    while (!temp.empty()) {
        array.append(QString::fromStdString(temp.top()));
        temp.pop();
    }
    return array;
}
stack<string> User::deserializeStacknotification(const QJsonArray& array) {
    vector<string> vec;
    for (const auto& val : array) {
        vec.push_back(val.toString().toStdString()); // convert QJsonValue to string
    }
    stack<string> s;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        s.push(*it);
    }
    return s;
}


// Amrkaamaal Kamolia2004$
// AhmedKaamaal Kamo2004$
// SalmaFathy Salma2005@
//SamaShourbagy Sam2006$
