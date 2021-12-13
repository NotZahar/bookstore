#ifndef SKWAREHOUSE_H
#define SKWAREHOUSE_H

#include <QWidget>

namespace Ui {
class SKWarehouse;
}

class SKWarehouse : public QWidget
{
    Q_OBJECT

public:
    explicit SKWarehouse(QWidget *parent = nullptr);
    ~SKWarehouse();

signals:
    void backFromWarehouseButtonWasPushed();

private slots:
    void backFromWarehouseButtonIsPushed(bool c);

private:
    Ui::SKWarehouse *ui;
};

#endif // SKWAREHOUSE_H
