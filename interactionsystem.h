#ifndef INTERACTIONSYSTEM_H
#define INTERACTIONSYSTEM_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class interactionsystem;
}

class interactionsystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit interactionsystem(User * user,QWidget *parent = nullptr);
    ~interactionsystem();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_logout_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_editpassword_clicked();

    void on_pushButton_checkpassword_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_BackfroEdit_clicked();
    // void refreshRequestsUI();
    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_saveButton_1_clicked();

    void on_pushButton_editusername_clicked();
    void on_Donate_button_clicked();
    void displayDonations();
   // void on_profilepicture_linkActivated(const QString &link);

   // void on_label_linkActivated(const QString &link);


    void on_notificationButton_clicked();

   // void on_notificationButton_clicked();

    void on_pushButton_6_clicked();

public:
   // static void on_profile_linkActivated(User*);
       QString tempImagePath;
    static void saveDonationImagePath();
   static void load_Donations_FromJson();
signals:
    void BACK();
private:
    User* current;
    Ui::interactionsystem *ui;
};

#endif // INTERACTIONSYSTEM_H
