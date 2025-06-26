#include "interactionsystem.h"
#include "ui_interactionsystem.h"
#include "user.h"
#include <QMessageBox>
#include<QInputDialog>
#include<QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include<QFile>
#include<QStandardPaths>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QInputDialog>
//#include <QTemporaryFile>
//#include <QMediaPlayer>
//#include <QAudioOutput>
interactionsystem::interactionsystem(User* user ,QWidget *parent) :
    QMainWindow(parent), current(user),
    ui(new Ui::interactionsystem)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->notificationsPanel->setVisible(false);


    ui->notificationButton->setFixedSize(80, 80);

    QIcon icon(":/img/iconn.png");
    ui->notificationButton->setIcon(icon);
    ui->notificationButton->setIconSize(QSize(64, 64));  // حجم الأيقونة 64x64

    ui->notificationButton->setText("");  // مفيش نص عشان الأيقونة بس

    ui->notificationButton->setContentsMargins(0, 0, 0, 0);

    ui->notificationButton->setStyleSheet(R"(
    QPushButton {
        border-radius: 40px;
        border: 2px solid transparent;
        padding: 0px;
        background-color: transparent;
    }
)");

    ui->notificationButton->setFocusPolicy(Qt::NoFocus);
    ui->notificationButton->setFlat(true);

    if (ui->notificationButton->parentWidget() && ui->notificationButton->parentWidget()->layout()) {
        ui->notificationButton->parentWidget()->layout()->setContentsMargins(0, 0, 0, 0);
        ui->notificationButton->parentWidget()->layout()->setSpacing(0);
    }

    ui->notificationButton->update();




  QPixmap rphoto(":/img/logo1.png");
    ui->logo_photo->setPixmap(rphoto);
    ui->logo_photo->setScaledContents(true);
    QPixmap rphoto1(":/img/logo1.png");
    ui->logo_photo_2->setPixmap(rphoto1);
    ui->logo_photo_2->setScaledContents(true);
    QPixmap rphoto2(":/img/logo1.png");
    ui->logo_photo_3->setPixmap(rphoto2);
    ui->logo_photo_3->setScaledContents(true);



    if (current) {
        QFile imageFile(current->getSelectedImagePath());
        if (!imageFile.exists()) {
            qDebug() << "Image file does not exist at path:" << current->getSelectedImagePath();
        } else {
            QPixmap pixmap(current->getSelectedImagePath());

            int labelSize = ui->profile->width(); // بافتراض إن الـ QLabel مربع
            if (!pixmap.isNull()) {
                QPixmap scaledPixmap = pixmap.scaled(labelSize, labelSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

                QPixmap roundPixmap(labelSize, labelSize);
                roundPixmap.fill(Qt::transparent);

                QPainter painter(&roundPixmap);
                painter.setRenderHint(QPainter::Antialiasing, true);

                QPainterPath path;
                path.addEllipse(0, 0, labelSize, labelSize);

                painter.setClipPath(path);
                painter.drawPixmap(0, 0, scaledPixmap);

                ui->profile->setPixmap(roundPixmap);
                ui->profile->setScaledContents(true);

                QString styleSheet =
                    "QLabel {"
                    "    border-radius: %1px;"
                    "    background-color: transparent;"
                    "    qproperty-alignment: AlignCenter;"
                    "}";

                styleSheet = styleSheet.arg(labelSize / 2);
                ui->profile->setStyleSheet(styleSheet);
            } else {
                ui->profile->clear();
            }
        }

        ui->userinfo_label->setText(QString::fromStdString(current->get_userName()));
    } else {
        qDebug() << "User pointer (current) is null!";
    }



                         }


interactionsystem::~interactionsystem()
{
    delete ui;
}

void interactionsystem::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void interactionsystem::on_pushButton_8_clicked()
{
    QString receivername = ui->receiverusername_label->text();
    QString receivernamelower = receivername.toLower();
    QString amount = ui->amount_request->text();

    string recfun = receivernamelower.toStdString();
    float amtfun = amount.toFloat();



    if (receivername.isEmpty() || amount.isEmpty()) {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please enter both name and amount.");

        msgBox.exec();
        return;
    }

    current->requestMoney(recfun, amtfun);
}



void interactionsystem::on_pushButton_logout_clicked()
{
    User::saveUsersToJson("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/users.json");
    Transaction::saveTransactionsToJson("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/alltransaction.json");
    emit BACK();
}


void interactionsystem::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void interactionsystem::on_pushButton_send_clicked()
{

    /*QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(100);


    player->setSource(QUrl("qrc:/sounds/sound/test_no_cover.mp3"));






    connect(player, &QMediaPlayer::mediaStatusChanged, this, [](QMediaPlayer::MediaStatus status){
        qDebug() << "Media status changed:" << status;
    });


    player->play();
    qDebug() << "Status:" << player->mediaStatus();*/

    QString usenamereceiver = ui->lineEdit_senduser->text();
    QString amountreceived = ui->lineEdit_sendamount->text();
    QString usernameignoreCase = usenamereceiver.toLower();
    string usernamefun = usernameignoreCase.toStdString();
    float amountrecfun = amountreceived.toFloat();



    if (usenamereceiver.isEmpty() || amountreceived.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please enter both name and amount.");

        msgBox.exec();
        return;
    }

    current->sendMoney(usernamefun, amountrecfun);
}


void interactionsystem::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_3->setCurrentWidget(ui->page_Empty);
    // current->viewBalance(1);
}


void interactionsystem::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QWidget* container = current->view_Transactions_History();
    ui->scrollArea_1->setWidget(container);
    ui->scrollArea_1->setWidgetResizable(true);
    current->view_Transactions_History();

}


void interactionsystem::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
    ui->stackedWidget_2->setCurrentWidget(ui->page_6);
}


void interactionsystem::on_pushButton_editpassword_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void interactionsystem::on_pushButton_checkpassword_clicked()
{
    QString passwordbeforenext = ui->passbeforeNEXT->text(); // input from user
    if (passwordbeforenext.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please fill the empty place.");

        msgBox.exec();
        return;
    }
    bool answer;
    answer= current->checkcurrentpassword(passwordbeforenext);

    if(answer){
        ui->stackedWidget_2->setCurrentIndex(2);
    }
    ui->passbeforeNEXT->clear();

}

void interactionsystem::on_pushButton_9_clicked()
{
    QString newpassword = ui->new_password_line->text();
    if (newpassword.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please fill the empty place.");

        msgBox.exec();
        return;
    }
    bool answer;
    answer= current->editpassword(newpassword);


    if (answer) {
        QMessageBox successBox;
        successBox.setWindowTitle("Success");
        successBox.setText("Password changed successfully!");
        successBox.exec();
    }
    ui->new_password_line->clear();
}


void interactionsystem::on_pushButton_BackfroEdit_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


// void interactionSystem::refreshRequestsUI() {
//     QWidget* newWidget = current->getRequestsWidget();
//     stackedWidget->removeWidget(oldWidget);
//     stackedWidget->addWidget(newWidget);
//     stackedWidget->setCurrentWidget(newWidget);
// }

/*void interactionsystem::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    QLayout* oldLayout = ui->scrollArea_2->widget() ? ui->scrollArea_2->widget()->layout() : nullptr;
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Create a new widget to hold the layout
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);

    if (current->hasRequests()) {
        Transaction request = current->getFrontRequest();

        QString requestDetails =
            "Sender: " + QString::fromStdString(request.getSender()) + "\n" +
            "Amount: " + QString::number(request.getamount()) + "\n" +
            "Date: " + QString::fromStdString(request.date);

        QLabel* label = new QLabel(requestDetails);
        QPushButton* acceptBtn = new QPushButton("Accept");
        QPushButton* declineBtn = new QPushButton("Decline");
        QPushButton* skipBtn = new QPushButton("Skip");

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(acceptBtn);
        buttonLayout->addWidget(declineBtn);
        buttonLayout->addWidget(skipBtn);

        layout->addWidget(label);
        layout->addLayout(buttonLayout);

        connect(acceptBtn, &QPushButton::clicked, this, [=]() {
            if (current->get_balance() >= request.getamount()) {
                current->sendMoney(request.getSender(), request.getamount());
                QMessageBox::information(this, "Accepted", "Money sent to " + QString::fromStdString(request.getSender()));
            } else {
                QMessageBox::warning(this, "Failed", "Insufficient balance.");
                current->skipFrontRequest();
            }
            current->popFrontRequest();
            on_pushButton_5_clicked();
        });

        connect(declineBtn, &QPushButton::clicked, this, [=]() {
            current->popFrontRequest();
            QMessageBox::information(this, "Declined", "Request declined.");
            on_pushButton_5_clicked();
        });

        connect(skipBtn, &QPushButton::clicked, this, [=]() {
            current->skipFrontRequest();
            QMessageBox::information(this, "Skipped", "Request skipped.");
            on_pushButton_5_clicked();
        });

    } else {
        QLabel* label = new QLabel("No Requests Found.");
        layout->addWidget(label);
    }

    contentWidget->setLayout(layout);
    ui->scrollArea_2->setWidget(contentWidget);
}*/

void interactionsystem::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    QLayout* oldLayout = ui->scrollArea_2->widget() ? ui->scrollArea_2->widget()->layout() : nullptr;
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Create a new widget to hold the layout
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);

    if (current->hasRequests()) {
        Transaction request = current->getFrontRequest();

        QString requestDetails =
            "Sender: " + QString::fromStdString(request.getSender()) + "\n" +
            "Amount: " + QString::number(request.getamount()) + "\n" +
            "Date: " + QString::fromStdString(request.date);

        QLabel* label = new QLabel(requestDetails);
        label->setStyleSheet(R"(
    background-color: rgb(240, 240, 240);
    border: 1px solid rgb(95, 48, 143);
    border-radius: 10px;
    padding: 15px;
    font: 600 14pt 'Segoe UI';
    color: rgb(95, 48, 143);
    margin-bottom: 15px;
)");
        QPushButton* acceptBtn = new QPushButton("Accept");
        QPushButton* declineBtn = new QPushButton("Decline");
        QPushButton* skipBtn = new QPushButton("Skip");

        // Button style
        QString btnStyle =
            "color: rgb(255, 255, 255);"
            "background: qlineargradient("
            "x1: 0, y1: 0, x2: 0, y2: 1, "
            "stop: 0 rgb(95, 48, 143), "
            "stop: 1 #D8A0E0);"
            "font: 700 15pt 'Segoe UI';"
            "border-radius: 40px;"
            "padding: 10px 20px;";

"padding: 10px 20px;";
        acceptBtn->setStyleSheet(btnStyle);
        declineBtn->setStyleSheet(btnStyle);
        skipBtn->setStyleSheet(btnStyle);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(acceptBtn);
        buttonLayout->addWidget(declineBtn);
        buttonLayout->addWidget(skipBtn);

        layout->addWidget(label);
        layout->addLayout(buttonLayout);



        connect(acceptBtn, &QPushButton::clicked, this, [=]() {
            if (current->get_balance() >= request.getamount()) {
                current->sendMoney(request.getSender(), request.getamount());

                QMessageBox msgBox;
                msgBox.setWindowTitle("Accepted");
                msgBox.setText("Money sent to " + QString::fromStdString(request.getSender()));

                QString notificationd = "You accepted a Request from " + QString::fromStdString(request.getSender()) +
                                        " for amount: " + QString::number(request.getamount())+" EGP ";
                current->notifications.push(notificationd.toStdString());


                QString senderNotif = QString::fromStdString(current->get_userName()) +
                                      " accepted your request for " + QString::number(request.getamount())+ " EGP ";
                 QString sender = QString::fromStdString(request.getSender());
               User::users[sender.toStdString()]->notifications.push(senderNotif.toStdString());



                msgBox.exec();
            } else {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Failed");
                msgBox.setText("Insufficient balance.");

                msgBox.exec();

                current->skipFrontRequest();
            }

            current->popFrontRequest();
            on_pushButton_5_clicked();
        });

        connect(declineBtn, &QPushButton::clicked, this, [=]() {
            current->popFrontRequest();

            QMessageBox msgBox;

            QString sender = QString::fromStdString(request.getSender());
            double amount = request.getamount();
            QString notificationd = "You declined a Request from " + sender +
                                    " for amount: " + QString::number(amount) + " EGP ";
            current->notifications.push(notificationd.toStdString());

            QString senderNotif = QString::fromStdString(current->get_userName()) +
                                  " declined your request for " + QString::number(amount)+ " EGP ";

            User::users[sender.toStdString()]->notifications.push(senderNotif.toStdString());
            msgBox.setWindowTitle("Declined");
            msgBox.setText("Request declined.");

            msgBox.exec();

            on_pushButton_5_clicked();
        });

        connect(skipBtn, &QPushButton::clicked, this, [=]() {
            current->skipFrontRequest();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Skipped");
            msgBox.setText("Request skipped.");

            msgBox.exec();

            on_pushButton_5_clicked();
        });

    } else {
        QLabel* label = new QLabel("No Requests Found.");
        label->setStyleSheet(R"(
    background-color: rgb(240, 240, 240);
    border: 1px solid rgb(95, 48, 143);
    border-radius: 10px;
    padding: 15px;
    font: 600 14pt 'Segoe UI';
    color: rgb(95, 48, 143);
    margin-bottom: 15px;
)");
        layout->addWidget(label);
    }

    contentWidget->setLayout(layout);
    ui->scrollArea_2->setWidget(contentWidget);
}

void interactionsystem::on_pushButton_10_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->page_EGP);
    ui->textBrowser_2->setText(current->viewBalance(1 , "EGP"));
}


void interactionsystem::on_pushButton_11_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->page_USD);
    ui->textBrowser_3->setText(current->viewBalance(50.78 , "$"));
}

void interactionsystem::on_pushButton_12_clicked()
{
    ui->stackedWidget_3->setCurrentWidget(ui->page_EUR);
    ui->textBrowser->setText(current->viewBalance(57.53 , "€"));

}




void interactionsystem::on_saveButton_1_clicked()
{
    QString newusername = ui->new_username_line->text();

    if (newusername.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Please fill the empty place");

        msgBox.exec();
        return;
    }
    else if (newusername.length() < 8) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Username Error");
        msgBox.setText("Username must be at least 8 characters long.");
        msgBox.exec();

    }
    else{
    bool answer;
    answer= current->editusername(newusername);



     if (answer) {
        QMessageBox successBox;
        successBox.setWindowTitle("Success");
        successBox.setText("Username changed successfully!");
        successBox.exec();
    }

    }

    ui->new_username_line->clear();
}


void interactionsystem::on_pushButton_editusername_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_11);
}

void interactionsystem::on_Donate_button_clicked()
{

   /* User::donations["bahia"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d1.jpg";
   // User::donations["57357@charity"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d6.png";
    User::donations["NationalAlliance"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d2.jpg";
    User::donations["masrelkheir"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d3.jpg";
    User::donations["resala"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d4.jpg";
    User::donations["magdyya3koub"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d5.png";
    User::donations["charity"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d7.jpg";
    User::donations["Associancharityforpourservir"] = "C:/dss/faroha/saloma/saloma/semi_final_version/SimpleDigitalWallet/d8.png";*/



    ui->stackedWidget->setCurrentIndex(7);
    displayDonations();
}
void interactionsystem::displayDonations() {
    QGridLayout* gridLayout = new QGridLayout();
    int index = 0;

    for (const auto& entry : User::donations) {
        const std::string& username = entry.first;
        const std::string& base64Image = entry.second;

        QByteArray byteArray = QByteArray::fromStdString(base64Image);
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromBase64(byteArray));


        QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + QString::fromStdString(username) + "_donation.png";
        pixmap.save(tempPath);

        QPushButton* button = new QPushButton();
        button->setFixedSize(150, 150);

        QString style = QString(R"(
    QPushButton {
        border: 2px solid black;
        border-radius: 15px;
        border-image: url(%1) 0 0 0 0 stretch stretch;
 background: qlineargradient(
            x1: 0, y1: 0, x2: 0, y2: 1,
            stop: 0 rgb(95, 48, 143),
            stop: 1 #D8A0E0
        );
    }
    QPushButton:hover {
        border: 2px solid white;
    }
)").arg(tempPath);

        button->setStyleSheet(style);



        connect(button, &QPushButton::clicked, [=]() {
            QInputDialog inputDialog;
            inputDialog.setWindowTitle("Enter amount");
            inputDialog.setLabelText("Please enter the amount of money:");
            inputDialog.setInputMode(QInputDialog::TextInput);
            inputDialog.resize(400, 200);

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
                    color: white;
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
                QString text = inputDialog.textValue();
                if (!text.isEmpty()) {
                    float amount = text.toFloat();
                    current->sendMoney(username, amount);
                } else {
                    QMessageBox msgBox;
                    msgBox.setText("You didn't enter the amount.");
                    msgBox.setWindowTitle("No amount");
                    msgBox.exec();
                }
            }
        });

        int row = index / 3;
        int col = index % 3;
        gridLayout->addWidget(button, row, col);
        index++;
    }

    QWidget* scrollWidget = new QWidget();
    scrollWidget->setLayout(gridLayout);
    ui->scrollArea_3->setWidget(scrollWidget);
    ui->scrollArea_3->setWidgetResizable(true);
}



/*void interactionsystem::saveDonationImagePath(  QString& username, QString& base64)
{

    QFile file("C:/dss/Final_project11/Final_project/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/donations.json");

    QJsonObject donationMap;

    // Step 1: Load existing data
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            donationMap = doc.object();
        }
        file.close();
    }

    // Step 2: Update or add new entry
    donationMap[username] = base64;

    // Step 3: Save back to file
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument saveDoc(donationMap);
        file.write(saveDoc.toJson());
        file.close();

        QMessageBox::information(nullptr, "Success", "Donation image saved successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Couldn't write to donations.json.");
    }
}*/
void interactionsystem::saveDonationImagePath()
{
    QFile file("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/donations.json");

    QJsonObject donationMap;


    for (const auto& pair : User::donations) {
        QString username = QString::fromStdString(pair.first);
        QString base64 = QString::fromStdString(pair.second);
        donationMap[username] = base64;
    }


    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument saveDoc(donationMap);
        file.write(saveDoc.toJson());
        file.close();

       // QMessageBox::information(nullptr, "Success", "All donation images saved successfully.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Couldn't write to donations.json.");
    }
}


void interactionsystem::load_Donations_FromJson()
{


    QFile file("C:/Users/salma/Documents/Shadaaa/Final_project11/Final_project/donations.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Couldn't open donations.json";
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (!doc.isObject()) {
        qDebug() << "Invalid JSON format!";
        return;
    }

    QJsonObject obj = doc.object();
    for (const QString& key : obj.keys()) {
        QString base64 = obj[key].toString();
        User::donations[key.toStdString()] = base64.toStdString();
    }

    file.close();
   }


void interactionsystem::on_notificationButton_clicked()
{
    bool isVisible = ui->notificationsPanel->isVisible();
    ui->notificationsPanel->setVisible(!isVisible);

    if (!isVisible) {


        ui->notificationsPanel->setStyleSheet("background-color: white; border-radius: 16px;");

        QGraphicsDropShadowEffect* panelShadow = new QGraphicsDropShadowEffect;
        panelShadow->setBlurRadius(25);
        panelShadow->setOffset(0, 5);
        panelShadow->setColor(QColor(0, 0, 0, 50));
        ui->notificationsPanel->setGraphicsEffect(panelShadow);

        QLayout* layout = ui->notificationsContent->layout();
        if (!layout) {
            layout = new QVBoxLayout(ui->notificationsContent);
            ui->notificationsContent->setLayout(layout);
        } else {
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != nullptr) {
                if (item->widget()) delete item->widget();
                delete item;
            }
        }

        std::stack<std::string> temp = current->notifications;
        int count = 1;

        if (temp.empty()) {
            QLabel* emptyLabel = new QLabel("No notifications found.");
            emptyLabel->setAlignment(Qt::AlignCenter);
            emptyLabel->setStyleSheet(R"(
                background-color: white;
                color: #555555;
                font: 600 16pt 'Segoe UI';
                border-radius: 12px;
                padding: 20px;
                margin: 20px;
            )");

            QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
            shadow->setBlurRadius(15);
            shadow->setOffset(0, 4);
            shadow->setColor(QColor(0, 0, 0, 60));
            emptyLabel->setGraphicsEffect(shadow);

            layout->addWidget(emptyLabel);
        } else {
            while (!temp.empty()) {
                QString notif = QString::fromStdString(temp.top());
                temp.pop();

                QString notifText = "<b>Notification #" + QString::number(count++) + "</b><br><br>" + notif;

                QLabel* label = new QLabel(notifText);
                label->setWordWrap(true);
                label->setTextFormat(Qt::RichText);
                label->setStyleSheet(R"(
                    background-color: white;
                    color: #333333;
                    font: 600 14pt 'Segoe UI';
                    border-radius: 16px;
                    padding: 15px;
                    margin: 10px;
                )");
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                label->setMaximumWidth(450);

                // ظل لكل إشعار
                QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
                shadow->setBlurRadius(15);
                shadow->setOffset(0, 4);
                shadow->setColor(QColor(0, 0, 0, 80));
                label->setGraphicsEffect(shadow);

                QWidget* wrapper = new QWidget;
                QHBoxLayout* wrapperLayout = new QHBoxLayout(wrapper);
                wrapperLayout->setContentsMargins(0, 0, 0, 0);
                wrapperLayout->setAlignment(Qt::AlignCenter);
                wrapperLayout->addWidget(label, 0, Qt::AlignCenter);

                wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

                layout->addWidget(wrapper);
            }
        }

        ui->notificationsScrollArea->setWidgetResizable(true);
        ui->notificationsScrollArea->setWidget(ui->notificationsContent);
        ui->notificationsContent->adjustSize();
        layout->invalidate();
        while(!current->notifications.empty())
        {
            current->notifications.pop();
        }
    }
}

/*
   void interactionsystem::on_notificationButton_clicked()
   {
       bool isVisible = ui->notificationsPanel->isVisible();
       ui->notificationsPanel->setVisible(!isVisible);

       if (!isVisible) {

           QLayout* layout = ui->notificationsContent->layout();
           if (!layout) {
               layout = new QVBoxLayout(ui->notificationsContent);
               ui->notificationsContent->setLayout(layout);
           } else {
               QLayoutItem* item;
               while ((item = layout->takeAt(0)) != nullptr) {
                   if (item->widget()) delete item->widget();
                   delete item;
               }
           }

           // 2. جهز البيانات من الـ stack
           std::stack<std::string> temp = current->notifications;
           int count = 1;

           if (temp.empty()) {
               QLabel* emptyLabel = new QLabel("No notifications found.");
               emptyLabel->setStyleSheet(R"(
                color: black;
                font: 20pt 'Segoe UI';
                padding: 10px;
                margin: 10px;
                text-align: center;
            )");
               layout->addWidget(emptyLabel);
           } else {
               while (!temp.empty()) {
                   QString notif = QString::fromStdString(temp.top());
                   temp.pop();

                   QString notifText = "<b>Notification #" + QString::number(count++) + "</b><br><br>" + notif;

                   QLabel* label = new QLabel(notifText);
                   label->setWordWrap(true);
                   label->setTextFormat(Qt::RichText);
                   label->setStyleSheet(R"(
                    background-color: rgb(126, 189, 189);
                    color: white;
                    font: 700 15pt 'Segoe UI';
                    border: 2px solid rgb(139, 105, 180);
                    border-radius: 12px;
                    padding: 15px;
                    margin: 10px;
                )");
                   label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                   label->setMaximumWidth(450);

                   QWidget* wrapper = new QWidget;
                   QHBoxLayout* wrapperLayout = new QHBoxLayout(wrapper);
                   wrapperLayout->setContentsMargins(0, 0, 0, 0);
                   wrapperLayout->setAlignment(Qt::AlignCenter);
                   wrapperLayout->addWidget(label, 0, Qt::AlignCenter);

                   wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

                   layout->addWidget(wrapper);
               }
           }

           ui->notificationsScrollArea->setWidgetResizable(true);
           ui->notificationsScrollArea->setWidget(ui->notificationsContent);
           ui->notificationsContent->adjustSize();
           layout->invalidate();
       }
       std::stack<std::string> debugStack = current->notifications;
       while (!debugStack.empty()) {
           std::cout << debugStack.top() << std::endl;
           debugStack.pop();
       }
   }

*/
   void interactionsystem::on_pushButton_6_clicked()
   {
       ui->stackedWidget_2->setCurrentWidget(ui->img);

       QString path = QFileDialog::getOpenFileName(
           this,
           "Select Profile Image",
           "",
           "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)"
           );

       if (!path.isEmpty()) {
           QPixmap pix(path);

           if (!pix.isNull()) {

               QSize labelSize = ui->imgLabel->size();
               int radius = qMin(labelSize.width(), labelSize.height()) / 2;


               QPixmap scaledPixmap = pix.scaled(labelSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
               QPixmap roundPixmap(labelSize);
               roundPixmap.fill(Qt::transparent);

               QPainter painter(&roundPixmap);
               painter.setRenderHint(QPainter::Antialiasing, true);
               QPainterPath pathClip;
               pathClip.addEllipse(0, 0, labelSize.width(), labelSize.height());
               painter.setClipPath(pathClip);
               painter.drawPixmap(0, 0, scaledPixmap);


               ui->imgLabel->setPixmap(roundPixmap);
               ui->imgLabel->setScaledContents(true);
               ui->imgLabel->setStyleSheet(
                   "border-radius: " + QString::number(radius) + "px;"
                                                                 "background-color: transparent;"
                   );


               ui->profile->setPixmap(roundPixmap);
               ui->profile->setScaledContents(true);
               ui->profile->setStyleSheet(
                   "border-radius: " + QString::number(radius) + "px;"
                                                                 "background-color: transparent;"
                   );


               current->setSelectedImagePath(path);
               tempImagePath = path;
           }
       }
   }

