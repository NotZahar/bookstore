#ifndef SKWAREHOUSE_H
#define SKWAREHOUSE_H

#include <QWidget>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QStringList>
#include <vector>
#include <utility>

#include "QDebug"

#include "../../bookstore.h"

namespace Ui {
class SKWarehouse;
}

class SKWarehouse : public QWidget
{
    Q_OBJECT

public:
    explicit SKWarehouse(QWidget *parent = nullptr);
    ~SKWarehouse();

    void updateWarehouseTable();
    void updateCartTable();

signals:
    void backFromWarehouseButtonWasPushed();

private slots:
    void backFromWarehouseButtonIsPushed(bool c);
    void insertIsStarted(bool c);
    void deleteIsStarted(bool c);
    void searchIsStarted(bool c);
    void clearCartIsStarted(bool c);

private:
    int getCartTableRowCount();

private:
    Ui::SKWarehouse *ui;

    QSqlTableModel *warehouseModel;
    QSqlTableModel *cartModel;
    const std::vector<std::pair<QString, QString>> bookcopyTableColumnNames;
    const std::vector<std::pair<QString, QString>> cartTableColumnNames;
};

#endif // SKWAREHOUSE_H
