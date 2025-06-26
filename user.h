#ifndef USER_H
#define USER_H
#include<stack>
#include<queue>
#include <unordered_map>
#include"Transaction.h"
#include <string>
#include <iostream>
#include <QWidget>
#include <regex>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QCryptographicHash>
#include<unordered_set>
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>

using namespace std;
class User
{
public:
    static unordered_map <string, User*> users;
    static unordered_map<string,string> donations;
    stack <string>notifications;

private:


    string userName;
    string password;
    string Email;
    float balance;
    bool isSuspended;
    stack<Transaction> transactions;
    queue<Transaction> requests;
    QWidget* parentWidget = nullptr;
    QString selectedImagePath;

    public:
    User(string userName, string password ,string email, QWidget* parent = nullptr);
    string get_userName();
    string get_password();
    string get_phoneNum();
    string getEmail();
    void setEmail(string);
    void setPassword(string);
    void setUsername(string);
    void set_balance(float);
    float get_balance();
    bool get_suspended();
    void registerUser(string, string);
    void login(string, string);
    void logout();
    QString viewBalance(float multiplier , string currency);
    void sendMoney(string , float);
    void requestMoney(string userName, float amount);
    QWidget* view_Transactions_History();
    void editUser();
    bool validUser(string);
    void viewRequests();
    queue<Transaction> getRequests();
    stack<Transaction> getTransaction();
    void set_suspended(bool status);

    bool loginconstraints(string);
    bool currentpasscorrect(string);
    QWidget* getRequestsWidget();

    static void loadUsersFromJson(const QString& filePath);
    static void saveUsersToJson(const QString& filePath);

    QJsonArray serializeStack(const stack<Transaction>& trans) const;
    QJsonArray serializeQueue(const queue<Transaction>& reqs) const;
    static stack<Transaction> deserializeStack(const QJsonArray& array);
    static queue<Transaction> deserializeQueue(const QJsonArray& array);
    static QString hashPassword(QString password);
    void popFrontRequest();
    void skipFrontRequest();
    Transaction getFrontRequest();
    bool hasRequests();

    void setSelectedImagePath( QString& path);
    QString getSelectedImagePath();

    void virewNotifications();

    bool editusername(QString);
    bool editpassword(QString);
    bool checkcurrentpassword(QString);
    static QJsonArray serializeStacknotification(const stack<string>& notifications) ;
    static stack<string> deserializeStacknotification(const QJsonArray& array);

};

#endif // USER_H
