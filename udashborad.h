#ifndef UDASHBORAD_H
#define UDASHBORAD_H

#include <QWidget>

namespace Ui {
class udashborad;
}

class udashborad : public QWidget
{
    Q_OBJECT

public:
    explicit udashborad(QWidget *parent = nullptr);
    ~udashborad();

private:
    Ui::udashborad *ui;
};

#endif // UDASHBORAD_H
