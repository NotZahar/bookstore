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
#include <QMap>

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

signals:
    void clientPaymentWasChosen();
    void backFromClientShopWasChosen();

private slots:
    void booksSearchWasStarted(bool c);
    void backFromClientShopIsChosen(bool c);

private:
    Ui::ClientsShopPage *ui;

    QSqlTableModel *booksSearchModel;
    const QMap<QString, QString> bookTableColumnNames;
};

#endif // CLIENTSSHOPPAGE_H
