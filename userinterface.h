#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include "userregister.h"
#include "userlogin.h"
#include "interactionsystem.h"
#include "admin.h"
namespace Ui {
class userinterface;
}

class userinterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit userinterface(QWidget *parent = nullptr);
    ~userinterface();

private slots:


    void on_pushButton_gotologin_clicked();

    void on_pushButton_login_2_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_Home_clicked();
    void signalBACK();
    void signalBACKFROMADMIN();


    void on_pushButton_clicked();

    void on_ForgetPasswordButton_clicked();



    void on_pushButton_continueForget_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



signals:
    void returnHome();

private:
    QString tempImagePath;  // هنا نخزن مسار الصورة بعد اختيارها

    Ui::userinterface *ui;
    interactionsystem * userdoing;
    User *currentUser = nullptr;
    Admin * cadmin;
     QString sentOtp;
};

#endif // USERINTERFACE_H
