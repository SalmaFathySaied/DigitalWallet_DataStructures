#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include <QWidget>


namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

    QString get_userName();
    QString get_password();

signals:
    void logoutClicked();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_Add_Radio_clicked();
    void on_withdraw_Radio_clicked();
    void on_ModifyButton_clicked();
    void on_buttonforSetfees_clicked();
    void on_highCombo_activated(int index);
    void on_lowCombo_activated(int index);
    void on_pushButton_13_clicked();
    void on_pushButton_10_clicked();
    void on_reactivateButton_clicked();
    void on_susspendButton_clicked();

private:
    Ui::Admin *ui;
    QString userName;
    QString password;
    QString operation;

    float highFeesRate=0.1f;
    float lowFeesRate=0.1f;
public:
    void login(QString username, QString password);
    void resetToLogin();
    void addUser();
    void deleteUser(QString username);
    void view_AlL_Users();
    void viewalltransactions();
    void ModifyBalance(QString username, float amount, QString operation);
    void changeUserPass(QString username, QString newPassword);
    void suspendAcc(QString username);
    void reactivateAcc(QString username);
    void setFees(float highRate, float lowRate);
    float AddFees(User* user, float amount);


};


#endif // ADMIN_H
