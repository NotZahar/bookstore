#include "skwarehouse.h"
#include "ui_skwarehouse.h"

SKWarehouse::SKWarehouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SKWarehouse),
    warehouseModel(nullptr),
    cartModel(nullptr),
    bookcopyTableColumnNames{{"код экземпляра", "copyid"},
                             {"уин", "uniqueinventorynumber"},
                             {"адрес склада", "warehouse"},
                             {"isbn", "isbn"}},
    cartTableColumnNames{{"код заказа", "orderid"},
                         {"код экземпляра", "copyid"}}
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &SKWarehouse::backFromWarehouseButtonIsPushed);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &SKWarehouse::searchIsStarted);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &SKWarehouse::deleteIsStarted);
    QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, &SKWarehouse::insertIsStarted);
    QObject::connect(ui->pushButton_5, &QPushButton::clicked, this, &SKWarehouse::clearCartIsStarted);

    // initialize and select warehouse
    warehouseModel = new QSqlTableModel(this, QSqlDatabase::database("main connection"));
    warehouseModel->setTable("bookcopy");

    for (int i = 0, j = 0; i < warehouseModel->columnCount(); ++i, ++j)
    {
        warehouseModel->setHeaderData(i, Qt::Horizontal, bookcopyTableColumnNames[j].first);
    }

    warehouseModel->setSort(0, Qt::AscendingOrder);
    warehouseModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    if (!warehouseModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", warehouseModel->lastError().text());
        return;
    }

    ui->tableView->setModel(warehouseModel);
    ui->tableView->repaint();

    // initialize and select cart
    cartModel = new QSqlTableModel(this, QSqlDatabase::database("main connection"));
    cartModel->setTable("cart");

    for (int i = 0, j = 0; i < cartModel->columnCount(); ++i, ++j)
    {
        cartModel->setHeaderData(i, Qt::Horizontal, cartTableColumnNames[j].first);
    }

    cartModel->setSort(0, Qt::AscendingOrder);
    cartModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    if (!cartModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", cartModel->lastError().text());
        return;
    }

    ui->tableView_2->setModel(cartModel);
    ui->tableView_2->repaint();
}

SKWarehouse::~SKWarehouse()
{
    delete ui;
}

void SKWarehouse::updateWarehouseTable()
{
    if (!warehouseModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", warehouseModel->lastError().text());
        return;
    }

    ui->tableView->repaint();
}

void SKWarehouse::updateCartTable()
{
    if (!cartModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", cartModel->lastError().text());
        return;
    }

    ui->tableView_2->repaint();
}

void SKWarehouse::backFromWarehouseButtonIsPushed(bool)
{
    emit backFromWarehouseButtonWasPushed();
}

void SKWarehouse::insertIsStarted(bool)
{
    QString insertWarehouseQueryString = "INSERT INTO bookcopy (copyid, "
                                         "uniqueinventorynumber, warehouse, isbn) "
                                         "VALUES (%1, %2, '%3', %4);";
    QSqlQuery insertWarehouseQuery(QSqlDatabase::database("main connection"));
    if (!insertWarehouseQuery.exec(insertWarehouseQueryString
                                  .arg(ui->lineEdit_2->text())
                                  .arg(ui->lineEdit_3->text())
                                  .arg(ui->lineEdit_4->text())
                                  .arg(ui->lineEdit_5->text())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    updateWarehouseTable();
}

void SKWarehouse::deleteIsStarted(bool)
{
    int deleteCount = warehouseModel->rowCount();
    for (int i = 0; i < deleteCount; ++i)
    {
        warehouseModel->removeRows(0, 1);

        if (!warehouseModel->submitAll())
        {
            QMessageBox::warning(nullptr, "ошибка при работе с базой данных", warehouseModel->lastError().text());
            return;
        }

        warehouseModel->select();
    }

    ui->tableView->repaint();
}

void SKWarehouse::searchIsStarted(bool)
{
    warehouseModel->setFilter(ui->comboBox->currentText() == "все" ?
                                          QString("copyid LIKE '%%1%' OR "
                                          "uniqueinventorynumber LIKE '%%1%' OR "
                                          "warehouse LIKE '%%1%' OR "
                                          "isbn LIKE '%%1%'")
                                          .arg(ui->lineEdit->text())
                                        : QString("%1 LIKE '%%2%'")
                                          .arg(bookcopyTableColumnNames[ui->comboBox->currentIndex() - 1].second)
                                          .arg(ui->lineEdit->text()));

    updateWarehouseTable();
}

void SKWarehouse::clearCartIsStarted(bool)
{
    QString deleteBookCopyFromCartQueryString = "DELETE FROM cart WHERE copyid = %1;";
    QSqlQuery deleteBookCopyFromCartQuery(QSqlDatabase::database("main connection"));

    QString deleteBookCopyFromWarehouseQueryString = "DELETE FROM bookcopy WHERE copyid = %1;";
    QSqlQuery deleteBookCopyFromWarehouseQuery(QSqlDatabase::database("main connection"));

    QString updateOrderStatusQueryString = "UPDATE ordering "
                                           "SET orderstatus = 'В пункте выдачи' "
                                           "WHERE orderid = %1;";
    QSqlQuery updateOrderStatusQuery(QSqlDatabase::database("main connection"));

    const int rowCount = getCartTableRowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        int orderid = cartModel->record(0).value("orderid").toInt();
        int copyid = cartModel->record(0).value("copyid").toInt();

        if (!updateOrderStatusQuery.exec(updateOrderStatusQueryString
                                         .arg(orderid)))
        {
            QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
            return;
        }

        if (!deleteBookCopyFromCartQuery.exec(deleteBookCopyFromCartQueryString
                                              .arg(copyid)))
        {
            QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
            return;
        }

        if (!deleteBookCopyFromWarehouseQuery.exec(deleteBookCopyFromWarehouseQueryString
                                     .arg(copyid)))
        {
            QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
            return;
        }

        cartModel->select();
        warehouseModel->select();
    }

    ui->tableView->repaint();
    ui->tableView_2->repaint();
}

int SKWarehouse::getCartTableRowCount()
{
    const int impossibleRowCount = -1;
    QString countQueryString = "SELECT COUNT(*) AS rowcount FROM cart;";

    QSqlQuery countQuery(QSqlDatabase::database("main connection"));
    if (!countQuery.exec(countQueryString))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return impossibleRowCount;
    }

    int rowCount = impossibleRowCount;
    if (countQuery.next())
    {
        rowCount = countQuery.value("rowcount").toInt();
    }

    return rowCount;
}
