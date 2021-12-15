#ifndef DPOPERATORSHOMEPAGE_H
#define DPOPERATORSHOMEPAGE_H

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
class DPOperatorsHomePage;
}

class DPOperatorsHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit DPOperatorsHomePage(QWidget *parent = nullptr);
    ~DPOperatorsHomePage();

    void displayDPOperatorData(const QList<QVariant> &data);

signals:
    void operatorExitedFromHomePage();
    void operatorWantedToGoToDP(QString DPAddress);

private slots:
    void operatorExitsFromHomePage(bool c);
    void goToDPButtonIsPushed(bool c);

private:
    Ui::DPOperatorsHomePage *ui;
};

#endif // DPOPERATORSHOMEPAGE_H
