#include "Transaction.h"
#include <stack>
using namespace std;

stack<Transaction> Transaction::alltransactions;


Transaction::Transaction(string sender, string receiver, float amount, string date) {
    this->sender = sender;
    this->receiver = receiver;
    this->amount = amount;
    this->date = date;
    time_t now = time(0);
    date = ctime(&now);
    if (!date.empty())
    {
        date.pop_back();
    }
  // alltransactions.push(*this);

}

Transaction::Transaction(string sender, string receiver, float amount)
{
    this->sender = sender;
    this->receiver = receiver;
    this->amount = amount;
    time_t now = time(0);
    date = ctime(&now);
    if (!date.empty())
    {
        date.pop_back();
    }

}

void Transaction::setamount(float amount)
{
    this->amount = amount;
}

void Transaction::setReceiver(string receivername)
{
    this->receiver = receivername;
}

void Transaction::setSender(string sendername)
{
    this->sender = sendername;
}

float Transaction::getamount() const
{
    return amount;
}

string Transaction::getSender() const
{
    return sender;
}

string Transaction::getReceiver() const
{
    return receiver;
}

QJsonObject Transaction::toJson() const
{
    QJsonObject obj;
    obj["sender"] = QString::fromStdString(sender);
    obj["receiver"] = QString::fromStdString(receiver);
    obj["amount"] = amount;
    obj["date"] = QString::fromStdString(date);
    return obj;
}
Transaction Transaction::fromJson(const QJsonObject& obj) {
    string sender = obj["sender"].toString().toStdString();
    string receiver = obj["receiver"].toString().toStdString();
    float amount = obj["amount"].toDouble();
    string date = obj["date"].toString().toStdString();
    return Transaction(sender, receiver, amount,date);
}
stack<Transaction> Transaction::deserializeStack(const QJsonArray& array) {
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
QJsonArray Transaction::serializeStack(const stack<Transaction>& trans) {
    QJsonArray array;
    stack<Transaction> temp = trans;
    while (!temp.empty()) {
        array.append(temp.top().toJson());
        temp.pop();
    }
    return array;
}

void Transaction::loadtransactionsFromJson(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isArray()) return;
    QJsonArray transactionsArray = doc.array();

    alltransactions = deserializeStack(transactionsArray);
}
void Transaction::saveTransactionsToJson(const QString& filePath)
{

    QJsonArray array = serializeStack(alltransactions);


    QJsonDocument doc(array);


    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) return;

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}


/*
void Transaction::saveTransactionsToJson(const QString& filePath)
{
    QJsonArray array;
    stack<Transaction> tempStack = alltransactions;


    vector<Transaction> vec;
    while (!tempStack.empty()) {
        vec.push_back(tempStack.top());
        tempStack.pop();
    }

    userObj["transactions"] = user->serializeStack(user->transactions);
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        array.append(it->toJson());
    }

    QJsonDocument doc(array);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) return;

    file.write(doc.toJson(QJsonDocument::Indented));  // نحفظ الملف بشكل مرتب
    file.close();
}
*/
