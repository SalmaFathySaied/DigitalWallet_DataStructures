#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include<stack>
#include <ctime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
using namespace std;
class Transaction
{
private:
    string sender;
    string receiver;
    float amount;


public:

     static stack<Transaction> alltransactions;
    string date;
   Transaction(string, string, float);
    Transaction(string sender, string receiver, float amount, string date);
    void setSender(string);
    void setReceiver(string);
    void setamount(float);
    string getSender() const;
    string getReceiver() const;
    float getamount() const;
    QJsonObject toJson() const;
    static Transaction fromJson(const QJsonObject& obj);
    static void loadtransactionsFromJson(const QString& filePath);
    static void saveTransactionsToJson(const QString& filePath);
    static stack<Transaction> deserializeStack(const QJsonArray& array);
    static   QJsonArray serializeStack(const stack<Transaction>& trans) ;

};

#endif // TRANSACTION_H
