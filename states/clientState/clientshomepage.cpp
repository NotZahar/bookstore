#include "clientshomepage.h"
#include "ui_clientshomepage.h"

ClientsHomePage::ClientsHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsHomePage),
    clientsOrdersDataModel(nullptr)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ClientsHomePage::clientExitsFromSystemButtonIsPushed);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &ClientsHomePage::goToShopButtonIsPushed);
}

ClientsHomePage::~ClientsHomePage()
{
    delete ui;
}

void ClientsHomePage::displayClientData(const QList<QVariant> &data)
{
    QString clientDataQueryString = "SELECT * FROM customer WHERE email = '%1';";
    QSqlQueryModel clientDataModel;
    clientDataModel.setQuery(clientDataQueryString.arg(data.at(0).toString()), QSqlDatabase::database("main connection"));

    if (clientDataModel.lastError().isValid())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", clientDataModel.lastError().text());
        return;
    }

    ui->label_8->setText(clientDataModel.record(0).value("surname").toString());
    ui->label_9->setText(clientDataModel.record(0).value("uname").toString());
    ui->label_10->setText(clientDataModel.record(0).value("patronymic").toString());
    ui->label_11->setText(clientDataModel.record(0).value("phone").toString());
    ui->label_12->setText(clientDataModel.record(0).value("email").toString());

    QString clientsOrdersDataQueryString = "SELECT orderdate AS 'Дата', ordertime AS "
                                           "'Время', orderstatus AS 'Статус', cost AS "
                                           "'Стоимость', paymentmethod AS 'Способ оплаты', "
                                           "(SELECT address FROM deliverypoint WHERE ordering.deliverypoint "
                                           "= deliverypoint.pointid) AS 'Пункт выдачи' FROM ordering WHERE customer = %1;";

    if (clientsOrdersDataModel != nullptr)
    {
        clientsOrdersDataModel->clear();
    }
    clientsOrdersDataModel = new QSqlQueryModel(ui->tableView);
    clientsOrdersDataModel->setQuery(clientsOrdersDataQueryString.arg(clientDataModel.record(0).value("clientid").toString()), QSqlDatabase::database("main connection"));

    if (clientsOrdersDataModel->lastError().isValid())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", clientsOrdersDataModel->lastError().text());
        return;
    }

    ui->tableView->setModel(clientsOrdersDataModel);
    ui->tableView->repaint();
}

void ClientsHomePage::goToShopButtonIsPushed()
{
    emit clientWantedToShop();
}

void ClientsHomePage::clientExitsFromSystemButtonIsPushed(bool)
{
    emit clientExitedFromHomePage();
}
