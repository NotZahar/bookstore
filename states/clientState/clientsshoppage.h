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
#include <vector>
#include <utility>
#include <algorithm>

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
    void updateCart();

signals:
    void backFromClientShopWasChosen();
    void orderWasMade(int orderId);

public slots:
    void booksSearchIsStarted(bool c = false);

private slots:
    void backFromClientShopIsChosen(bool c);
    void inCartButtonIsPushed(bool c);
    void orderButtonIsPushed(bool c);

private:
    int getClientId();
    int getCurrentOrderid();
    int getAmountOfCurrentISBNs();
    void changeCurrentOrderStatus();

private:
    Ui::ClientsShopPage *ui;

    QString customerEmail;
    QSqlQueryModel *booksSearchModel;
    QSqlQueryModel *currentCartModel;
    const int impossibleOrderId;
    const int impossibleClientId;
    int currentOrderId;
    int currentOrderTotalCost;
    const std::vector<std::pair<QString, QString>> bookTableColumnNames;
};

#endif // CLIENTSSHOPPAGE_H
