#ifndef CLIENTSHOMEPAGE_H
#define CLIENTSHOMEPAGE_H

#include <QWidget>
#include <QList>
#include <QVariant>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMessageBox>

#include "../../bookstore.h"

namespace Ui {
class ClientsHomePage;
}

class ClientsHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsHomePage(QWidget *parent = nullptr);
    ~ClientsHomePage();

    void displayClientData(const QList<QVariant> &data);
    QString getEmail();

signals:
    void clientWantedToShop();
    void clientExitedFromHomePage();

private slots:
    void goToShopButtonIsPushed();
    void clientExitsFromSystemButtonIsPushed(bool c);

private:
    Ui::ClientsHomePage *ui;

    QSqlQueryModel *clientsOrdersDataModel;
};

#endif // CLIENTSHOMEPAGE_H
