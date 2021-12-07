#include "clientshomepage.h"
#include "ui_clientshomepage.h"

ClientsHomePage::ClientsHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsHomePage)
{
    ui->setupUi(this);
}

ClientsHomePage::~ClientsHomePage()
{
    delete ui;
}
