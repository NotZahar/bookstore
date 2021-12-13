#ifndef STOREKEEPERSBOOKS_H
#define STOREKEEPERSBOOKS_H

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

#include "../../bookstore.h"

namespace Ui {
class StoreKeepersBooks;
}

class StoreKeepersBooks : public QWidget
{
    Q_OBJECT

public:
    explicit StoreKeepersBooks(QWidget *parent = nullptr);
    ~StoreKeepersBooks();

    void updateBooksTable();

signals:
    void backFromBooksButtonWasPushed();

private slots:
    void backFromBooksButtonIsPushed(bool c);
    void insertIsStarted(bool c);
    void deleteIsStarted(bool c);
    void searchIsStarted(bool c);

private:
    Ui::StoreKeepersBooks *ui;

    QSqlTableModel *booksModel;
    const std::vector<std::pair<QString, QString>> booksTableColumnNames;
};

#endif // STOREKEEPERSBOOKS_H
