#include "storekeepersbooks.h"
#include "ui_storekeepersbooks.h"

StoreKeepersBooks::StoreKeepersBooks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreKeepersBooks),
    booksModel(nullptr),
    booksTableColumnNames{{"isbn", "isbn"},
                          {"название книги", "booktitle"},
                          {"авторы", "authorsnames"},
                          {"город издания", "cityofpublication"},
                          {"издательство", "publisher"},
                          {"год издания", "yearofpublication"},
                          {"кол-во страниц", "pagecount"},
                          {"категория", "category"},
                          {"стоимость", "cost"}}
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &StoreKeepersBooks::searchIsStarted);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &StoreKeepersBooks::deleteIsStarted);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &StoreKeepersBooks::insertIsStarted);
    QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, &StoreKeepersBooks::backFromBooksButtonIsPushed);

    // initialize and select
    booksModel = new QSqlTableModel(this, QSqlDatabase::database("main connection"));
    booksModel->setTable("book");

    for (int i = 0, j = 0; i < booksModel->columnCount(); ++i, ++j)
    {
        booksModel->setHeaderData(i, Qt::Horizontal, booksTableColumnNames[j].first);
    }

    booksModel->setSort(0, Qt::AscendingOrder);
    booksModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    if (!booksModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", booksModel->lastError().text());
        return;
    }

    ui->tableView->setModel(booksModel);
    ui->tableView->repaint();
}

StoreKeepersBooks::~StoreKeepersBooks()
{
    delete ui;
}

void StoreKeepersBooks::updateBooksTable()
{
    if (!booksModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", booksModel->lastError().text());
        return;
    }

    ui->tableView->repaint();
}

void StoreKeepersBooks::backFromBooksButtonIsPushed(bool)
{
    updateBooksTable();
    emit backFromBooksButtonWasPushed();
}

void StoreKeepersBooks::insertIsStarted(bool)
{
    QString insertBookQueryString = "INSERT INTO book (isbn, booktitle, authorsnames, "
                                    "cityofpublication, publisher, yearofpublication, "
                                    "pagecount, category, cost) "
                                    "VALUES (%1, '%2', '%3', '%4', '%5', '%6', "
                                    "%7, '%8', %9);";
    QSqlQuery insertBookQuery(QSqlDatabase::database("main connection"));
    if (!insertBookQuery.exec(insertBookQueryString
                                  .arg(ui->lineEdit_2->text())
                                  .arg(ui->lineEdit_3->text())
                                  .arg(ui->lineEdit_4->text())
                                  .arg(ui->lineEdit_5->text())
                                  .arg(ui->lineEdit_6->text())
                                  .arg(ui->lineEdit_7->text())
                                  .arg(ui->lineEdit_8->text())
                                  .arg(ui->lineEdit_9->text())
                                  .arg(ui->lineEdit_10->text())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    updateBooksTable();
}

void StoreKeepersBooks::deleteIsStarted(bool)
{
    int deleteCount = booksModel->rowCount();
    for (int i = 0; i < deleteCount; ++i)
    {
        booksModel->removeRows(0, 1);

        if (!booksModel->submitAll())
        {
            QMessageBox::warning(nullptr, "ошибка при работе с базой данных", booksModel->lastError().text());
            return;
        }

        booksModel->select();
    }

    ui->tableView->repaint();
}

void StoreKeepersBooks::searchIsStarted(bool)
{
    booksModel->setFilter(ui->comboBox->currentText() == "все" ?
                                          QString("isbn LIKE '%%1%' OR "
                                          "booktitle LIKE '%%1%' OR "
                                          "authorsnames LIKE '%%1%' OR "
                                          "cityofpublication LIKE '%%1%' OR "
                                          "publisher LIKE '%%1%' OR "
                                          "yearofpublication LIKE '%%1%' OR "
                                          "pagecount LIKE '%%1%' OR "
                                          "category LIKE '%%1%' OR "
                                          "cost LIKE '%%1%'")
                                          .arg(ui->lineEdit->text())
                                        : QString("%1 LIKE '%%2%'")
                                          .arg(booksTableColumnNames[ui->comboBox->currentIndex() - 1].second)
                                          .arg(ui->lineEdit->text()));

    updateBooksTable();
}
