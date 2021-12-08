#include "clientsshoppage.h"
#include "ui_clientsshoppage.h"

ClientsShopPage::ClientsShopPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsShopPage),
    booksSearchModel(nullptr),
    bookTableColumnNames({{"isbn", "isbn"},
                          {"название книги", "booktitle"},
                          {"авторы", "authorsnames"},
                          {"город издания", "cityofpublication"},
                          {"издательство", "publisher"},
                          {"год издания", "yearofpublication"},
                          {"кол-во страниц", "pagecount"},
                          {"категория", "category"},
                          {"стоимость", "cost"}})
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ClientsShopPage::booksSearchIsStarted);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &ClientsShopPage::backFromClientShopIsChosen);

    emit ui->pushButton->clicked();
}

ClientsShopPage::~ClientsShopPage()
{
    delete ui;
}

void ClientsShopPage::booksSearchIsStarted(bool)
{
    QString booksSearchQueryColumnAliasesString;
    for (unsigned long long i = 0; i < bookTableColumnNames.size(); ++i)
    {
        booksSearchQueryColumnAliasesString += "book." + bookTableColumnNames[i].second + " AS '" + bookTableColumnNames[i].first + "'";
        if (i != bookTableColumnNames.size() - 1)
        {
            booksSearchQueryColumnAliasesString += ", ";
        }
    }

    QString booksSearchQueryString = ( ui->comboBox->currentText() == "все" ?
                                       QString("SELECT %1 "
                                               "FROM book JOIN bookcopy ON book.isbn = bookcopy.isbn "
                                               "WHERE book.isbn LIKE '%%2%' OR book.booktitle LIKE '%%2%' "
                                               "OR book.authorsnames LIKE '%%2%' OR book.cityofpublication LIKE '%%2%' "
                                               "OR book.publisher LIKE '%%2%' OR book.yearofpublication LIKE '%%2%' "
                                               "OR book.pagecount LIKE '%%2%' OR book.category LIKE '%%2%' "
                                               "OR book.cost LIKE '%%2%'"
                                               "GROUP BY book.isbn;")
                                           .arg(booksSearchQueryColumnAliasesString)
                                           .arg(ui->lineEdit->text())
                                     : QString("SELECT %1 "
                                               "FROM book JOIN bookcopy ON book.isbn = bookcopy.isbn "
                                               "WHERE book.%2 LIKE '%%3%';"
                                               "GROUP BY book.isbn")
                                           .arg(booksSearchQueryColumnAliasesString)
                                           .arg( std::find_if(bookTableColumnNames.cbegin(),
                                                             bookTableColumnNames.cend(),
                                                             [this](const std::pair<QString, QString> &pair)
                                                             {
                                                                return pair.first == ui->comboBox->currentText();
                                                             })->second )
                                           .arg(ui->lineEdit->text()) );

    if (booksSearchModel != nullptr)
    {
        booksSearchModel->clear();
    }

    booksSearchModel = new QSqlQueryModel(ui->tableView_2);
    booksSearchModel->setQuery(booksSearchQueryString, QSqlDatabase::database("main connection"));

    auto it = bookTableColumnNames.cbegin();
    for (int i = 0; i < booksSearchModel->columnCount(); ++i, ++it)
    {
        booksSearchModel->setHeaderData(i, Qt::Horizontal, it->first);
    }

    if (booksSearchModel->lastError().isValid())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", booksSearchModel->lastError().text());
        return;
    }

    ui->tableView_2->setModel(booksSearchModel);
    ui->tableView_2->repaint();
}

void ClientsShopPage::backFromClientShopIsChosen(bool)
{
    // !!!!!!!!!!!!!!!!!!!!!!!

    emit backFromClientShopWasChosen();
}
