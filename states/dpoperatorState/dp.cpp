#include "dp.h"
#include "ui_dp.h"

DP::DP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DP),
    currentDPAddress(),
    ordersModel(nullptr),
    ordersTableColumnNames{{"код заказа", "orderid"},
                           {"дата", "orderdate"},
                           {"время", "ordertime"},
                           {"статус", "orderstatus"},
                           {"стоимость", "cost"},
                           {"способ оплаты", "paymentmethod"},
                           {"код клиента", "customer"}}
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &DP::searchIsStarted);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &DP::deleteIsStarted);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &DP::operatorExitsFromDP);
}

DP::~DP()
{
    delete ui;
}

void DP::setDPAdress(QString DPAddress)
{
    currentDPAddress = DPAddress;
}

void DP::updateOrdersTable()
{
    QString updateOrdersTableQueryString = "SELECT orderid AS 'код заказа', "
                                           "orderdate AS 'дата', "
                                           "ordertime AS 'время', "
                                           "orderstatus AS 'статус', "
                                           "cost AS 'стоимость', "
                                           "paymentmethod AS 'способ оплаты', "
                                           "customer.clientid AS 'код клиента', "
                                           "customer.uname AS 'имя клиента', "
                                           "customer.email AS 'email клиента' "
                                           "FROM ordering JOIN customer JOIN deliverypoint "
                                           "ON (ordering.customer = customer.clientid "
                                           "AND ordering.deliverypoint = deliverypoint.pointid) "
                                           "WHERE deliverypoint.address = '%1' "
                                           "AND ordering.orderstatus = 'В пункте выдачи';";

    if (ordersModel != nullptr)
    {
        ordersModel->clear();
    }

    ordersModel = new QSqlQueryModel(ui->tableView);
    ordersModel->setQuery(updateOrdersTableQueryString.arg(currentDPAddress), QSqlDatabase::database("main connection"));

    if (ordersModel->lastError().isValid())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", ordersModel->lastError().text());
        return;
    }

    ui->tableView->setModel(ordersModel);
    ui->tableView->repaint();
}

void DP::operatorExitsFromDP(bool)
{
    emit backFromDPWasChosen();
}

void DP::deleteIsStarted(bool)
{
    if (ordersModel->record(0).isEmpty())
    {
        return;
    }

    QString deleteOrderQueryString = "DELETE FROM ordering WHERE orderid = %1;";
    QSqlQuery deleteOrderQuery(QSqlDatabase::database("main connection"));
    if (!deleteOrderQuery.exec(deleteOrderQueryString
                                 .arg(ordersModel->record(0).value("код заказа").toInt())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    updateOrdersTable();
}

void DP::searchIsStarted(bool)
{
    QString ordersSearchQueryString = ( ui->comboBox->currentText() == "все"
                                        ? QString("SELECT orderid AS 'код заказа', "
                                                  "orderdate AS 'дата', "
                                                  "ordertime AS 'время', "
                                                  "orderstatus AS 'статус', "
                                                  "cost AS 'стоимость', "
                                                  "paymentmethod AS 'способ оплаты', "
                                                  "customer.clientid AS 'код клиента', "
                                                  "customer.uname AS 'имя клиента', "
                                                  "customer.email AS 'email клиента' "
                                                  "FROM ordering JOIN customer JOIN deliverypoint "
                                                  "ON (ordering.customer = customer.clientid "
                                                  "AND ordering.deliverypoint = deliverypoint.pointid) "
                                                  "WHERE deliverypoint.address = '%1' "
                                                  "AND ordering.orderstatus = 'В пункте выдачи' "
                                                  "AND (ordering.orderid LIKE '%%2%' OR "
                                                  "ordering.orderdate LIKE '%%2%' OR "
                                                  "ordering.ordertime LIKE '%%2%' OR "
                                                  "ordering.orderstatus LIKE '%%2%' OR "
                                                  "ordering.cost LIKE '%%2%' OR "
                                                  "ordering.paymentmethod LIKE '%%2%' OR "
                                                  "ordering.customer LIKE '%%2%');")
                                           .arg(currentDPAddress)
                                           .arg(ui->lineEdit->text().simplified())
                                        : QString("SELECT orderid AS 'код заказа', "
                                                  "orderdate AS 'дата', "
                                                  "ordertime AS 'время', "
                                                  "orderstatus AS 'статус', "
                                                  "cost AS 'стоимость', "
                                                  "paymentmethod AS 'способ оплаты', "
                                                  "customer.clientid AS 'код клиента', "
                                                  "customer.uname AS 'имя клиента', "
                                                  "customer.email AS 'email клиента' "
                                                  "FROM ordering JOIN customer JOIN deliverypoint "
                                                  "ON (ordering.customer = customer.clientid "
                                                  "AND ordering.deliverypoint = deliverypoint.pointid) "
                                                  "WHERE deliverypoint.address = '%1' "
                                                  "AND ordering.orderstatus = 'В пункте выдачи' "
                                                  "AND ordering.%2 LIKE '%%3%';")
                                           .arg(currentDPAddress)
                                           .arg(ordersTableColumnNames[ui->comboBox->currentIndex() - 1].second)
                                           .arg(ui->lineEdit->text().simplified()) );

    if (ordersModel != nullptr)
    {
        ordersModel->clear();
    }

    ordersModel = new QSqlQueryModel(ui->tableView);
    ordersModel->setQuery(ordersSearchQueryString, QSqlDatabase::database("main connection"));

    if (ordersModel->lastError().isValid())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", ordersModel->lastError().text());
        return;
    }

    ui->tableView->setModel(ordersModel);
    ui->tableView->repaint();
}
