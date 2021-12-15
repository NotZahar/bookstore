#ifndef STOREKEEPERSHOMEPAGE_H
#define STOREKEEPERSHOMEPAGE_H

#include <QWidget>
#include <QList>
#include <QVariant>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDate>

namespace Ui {
class StoreKeepersHomePage;
}

class StoreKeepersHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit StoreKeepersHomePage(QWidget *parent = nullptr);
    ~StoreKeepersHomePage();

    void displayEmployeeData(const QList<QVariant> &data);

signals:
    void storeKeeperExitedFromHomePage();
    void goToWarehouseButtonWasPushed();
    void goToBooksButtonWasPushed();

private slots:
    void storeKeeperExitsFromHomePage(bool c);
    void goToWarehouseButtonIsPushed(bool c);
    void goToBooksButtonIsPushed(bool c);

private:
    Ui::StoreKeepersHomePage *ui;
};

#endif // STOREKEEPERSHOMEPAGE_H
