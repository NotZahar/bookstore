#include "clientsshoppage.h"
#include "ui_clientsshoppage.h"

ClientsShopPage::ClientsShopPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsShopPage),
    customerEmail(),
    booksSearchModel(nullptr),
    cartModel(nullptr),
    impossibleOrderId(-1),
    impossibleClientId(-1),
    impossibleCurrentOrderTotalCost(-1),
    currentOrderId(impossibleOrderId),
    currentOrderTotalCost(impossibleCurrentOrderTotalCost),
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
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &ClientsShopPage::inCartButtonIsPushed);
}

ClientsShopPage::~ClientsShopPage()
{
    delete ui;
}

void ClientsShopPage::setClientEmail(QString clientEmail)
{
    customerEmail = clientEmail;
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
    booksSearchQueryColumnAliasesString += ", COUNT(*) AS 'в наличии'";

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
                                           .arg(ui->lineEdit->text().simplified())
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
                                           .arg(ui->lineEdit->text().simplified()) );

    if (booksSearchModel != nullptr)
    {
        booksSearchModel->clear();
    }

    booksSearchModel = new QSqlQueryModel(ui->tableView_2);
    booksSearchModel->setQuery(booksSearchQueryString, QSqlDatabase::database("main connection"));

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

void ClientsShopPage::inCartButtonIsPushed(bool)
{
    booksSearchIsStarted();

    for (int i = 0; i < getAmountOfBookCopies(); ++i)
    {

        // booksSearchModel->record(i).value("isbn").toInt();
    }

    QString cartModelQueryString = "";

    if (cartModel != nullptr)
    {
        cartModel->clear();
    }

    cartModel = new QSqlQueryModel(ui->tableView);
    cartModel->setQuery(cartModelQueryString, QSqlDatabase::database("main connection"));

    if (cartModel->lastError().isValid())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", cartModel->lastError().text());
        return;
    }

    ui->tableView->setModel(cartModel);
    ui->tableView->repaint();

    /*
    for (int i = 0; i < amountOfBookCopies; ++i)
    {
        booksSearchModel->record(i).value("isbn").toInt();
    }*/

    /*QString cartQueryString;
    for (int i = 0; i < amountOfBookCopies; ++i)
    {
        cartQueryString += "INSERT INTO cart VALUES (";
        cartQueryString += ;
        cartQueryString += ", ";
        cartQueryString += ;
        cartQueryString += "); ";
    }

    clientDataModel.record(0).value("surname").toString()

    qDebug() << cartQueryString;*/

    /*QSqlQuery checkQuery(QSqlDatabase::database("main connection"));
    QString checkQueryString = "SELECT * FROM Librarian WHERE (Login = '%2' OR Email = '%3' OR PhoneNumber = '%4');";

    if (!checkQuery.exec(checkQueryString
                         .arg(ui->lineEdit->text())
                         .arg(ui->lineEdit_5->text())
                         .arg(ui->lineEdit_6->text())))
    {
        QMessageBox::warning(nullptr, "Проблема с подключением к базе данных", "Ошибка запроса");
        return;
    }

    if (checkQuery.next())
    {
        QMessageBox::critical(nullptr, "Ошибка ввода", "Пользователь с такими логином или E-mail или номером уже зарегистрирован");
        return;
    }*/

    /*if (cartModel != nullptr)
    {
        cartModel->clear();
    }

    cartModel = new QSqlQueryModel(ui->tableView);
    cartModel->setQuery(cartQueryString, QSqlDatabase::database("main connection"));

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
    ui->tableView_2->repaint();*/
}

int ClientsShopPage::getClientId()
{
    QString getClientIdQueryString = "SELECT * FROM customer WHERE email = '%1';";
    QSqlQuery getClientIdQuery(QSqlDatabase::database("main connection"));
    if (!getClientIdQuery.exec(getClientIdQueryString.arg(customerEmail)))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return impossibleClientId;
    }

    int clientId = impossibleClientId;
    if (getClientIdQuery.next())
    {
        clientId = getClientIdQuery.value("clientid").toInt();
    }

    return clientId;
}

void ClientsShopPage::addNewOrder()
{
    QString addNewOrderQueryString = "INSERT INTO ordering (orderdate, ordertime, "
                                     "orderstatus, cost, paymentmethod, customer, "
                                     "deliverypoint) values (curdate(), curtime(), "
                                     "'Пустой', 0, 'Онлайн', %1, 1);";
    QSqlQuery addNewOrderQuery(QSqlDatabase::database("main connection"));
    if (!addNewOrderQuery.exec(addNewOrderQueryString.arg(getClientId())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    currentOrderId = getCurrentOrderid();
}

int ClientsShopPage::getCurrentOrderid()
{
    QString getCurrentOrderIdQueryString = "SELECT * FROM ordering ORDER BY orderid DESC LIMIT 1;";
    QSqlQuery getCurrentOrderIdQuery(QSqlDatabase::database("main connection"));
    if (!getCurrentOrderIdQuery.exec(getCurrentOrderIdQueryString))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return impossibleOrderId;
    }

    int curOrderId = impossibleOrderId;
    if (getCurrentOrderIdQuery.next())
    {
        curOrderId = getCurrentOrderIdQuery.value("orderid").toInt();
    }

    return curOrderId;
}

int ClientsShopPage::getAmountOfBookCopies()
{
    const int impossibleAmountOfBookCopies = -1;
    QString countQueryString = "SELECT COUNT(*) AS bookcopiescount FROM (";
    countQueryString += [this]()
                        {
                            QString lastQueryString = booksSearchModel->query().lastQuery();
                            lastQueryString.chop(1);
                            return lastQueryString;
                        }();
    countQueryString += ") AS rowcount;";

    QSqlQuery countQuery(QSqlDatabase::database("main connection"));
    if (!countQuery.exec(countQueryString))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return impossibleAmountOfBookCopies;
    }

    int amountOfBookCopies = impossibleAmountOfBookCopies;
    if (countQuery.next())
    {
        amountOfBookCopies = countQuery.value("bookcopiescount").toInt();
    }

    return amountOfBookCopies;
}
