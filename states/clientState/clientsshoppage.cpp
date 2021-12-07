#include "clientsshoppage.h"
#include "ui_clientsshoppage.h"

ClientsShopPage::ClientsShopPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsShopPage)
{
    ui->setupUi(this);
}

ClientsShopPage::~ClientsShopPage()
{
    delete ui;
}
