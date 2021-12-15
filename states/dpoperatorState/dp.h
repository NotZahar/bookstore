#ifndef DP_H
#define DP_H

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

#include "../../bookstore.h"

namespace Ui {
class DP;
}

class DP : public QWidget
{
    Q_OBJECT

public:
    explicit DP(QWidget *parent = nullptr);
    ~DP();

    void setDPAdress(QString DPAddress);
    void updateOrdersTable();

signals:
    void backFromDPWasChosen();

private slots:
    void operatorExitsFromDP(bool c);
    void deleteIsStarted(bool c);
    void searchIsStarted(bool c);

private:
    Ui::DP *ui;

    QString currentDPAddress;
    QSqlQueryModel *ordersModel;
    const std::vector<std::pair<QString, QString>> ordersTableColumnNames;
};

#endif // DP_H
