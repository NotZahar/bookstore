#include "skwarehouse.h"
#include "ui_skwarehouse.h"

SKWarehouse::SKWarehouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SKWarehouse)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &SKWarehouse::backFromWarehouseButtonIsPushed);
}

SKWarehouse::~SKWarehouse()
{
    delete ui;
}

void SKWarehouse::backFromWarehouseButtonIsPushed(bool)
{
    emit backFromWarehouseButtonWasPushed();
}
