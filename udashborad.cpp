#include "udashborad.h"
#include "ui_udashboard.h"


udashborad::udashborad(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::udashborad)
{
    ui->setupUi(this);
}

udashborad::~udashborad()
{
    delete ui;
}
