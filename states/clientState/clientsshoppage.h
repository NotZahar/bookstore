#ifndef CLIENTSSHOPPAGE_H
#define CLIENTSSHOPPAGE_H

#include <QWidget>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QString>
#include <vector>
#include <utility>
#include <algorithm>
#include <QDebug>

#include "../../bookstore.h"

namespace Ui {
class ClientsShopPage;
}

class ClientsShopPage : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsShopPage(QWidget *parent = nullptr);
    ~ClientsShopPage();

    void setClientEmail(QString clientEmail);
    void addNewOrder();

signals:
    void clientPaymentWasChosen();
    void backFromClientShopWasChosen();

public slots:
    void booksSearchIsStarted(bool c = false);

private slots:
    void backFromClientShopIsChosen(bool c);
    void inCartButtonIsPushed(bool c);

private:
    Ui::ClientsShopPage *ui;

    QString customerEmail;
    QSqlQueryModel *booksSearchModel;
    QSqlQueryModel *cartModel;
    const int impossibleOrderId;
    const int impossibleClientId;
    const int impossibleCurrentOrderTotalCost;
    int currentOrderId;
    int currentOrderTotalCost;
    const std::vector<std::pair<QString, QString>> bookTableColumnNames;

    int getClientId();
    int getCurrentOrderid();
    int getAmountOfCurrentISBNs();
};

#endif // CLIENTSSHOPPAGE_H
