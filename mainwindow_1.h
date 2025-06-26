#ifndef MAINWINDOW_1_H
#define MAINWINDOW_1_H

#include <QMainWindow>
#include "userinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    // void on_pushButton_clicked();
    void on_getStartedButton_clicked();

private:
    Ui::MainWindow *ui;
    userinterface * us;
};
#endif // MAINWINDOW_1_H
