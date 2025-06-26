#ifndef MAINWINDOW_1_H
#define MAINWINDOW_1_H

#include <QMainWindow>
#include "userinterface.h"
#include "admin.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_GetStarted_clicked();
    void ReturnHome();


private:
    Ui::MainWindow *ui;
userinterface *userRegorLogin;

};

#endif // MAINWINDOW_1_H
