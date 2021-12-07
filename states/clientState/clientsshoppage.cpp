#include "clientsshoppage.h"
#include "ui_clientsshoppage.h"

ClientsShopPage::ClientsShopPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsShopPage),
    booksSearchModel(nullptr),
    bookTableColumnNames({std::make_pair<QString, QString>("isbn", "isbn"),
                         std::make_pair<QString, QString>("название книги", "booktitle"),
                         std::make_pair<QString, QString>("авторы", "authorsnames"),
                         std::make_pair<QString, QString>("город издания", "cityofpublication"),
                         std::make_pair<QString, QString>("издательство", "publisher"),
                         std::make_pair<QString, QString>("год издания", "yearofpublication"),
                         std::make_pair<QString, QString>("кол-во страниц", "pagecount"),
                         std::make_pair<QString, QString>("категория", "category"),
                         std::make_pair<QString, QString>("стоимость", "cost")})
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ClientsShopPage::booksSearchWasStarted);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &ClientsShopPage::backFromClientShopIsChosen);

    emit ui->pushButton->clicked();
}

ClientsShopPage::~ClientsShopPage()
{
    delete ui;
}

void ClientsShopPage::booksSearchWasStarted(bool)
{
    if (booksSearchModel != nullptr)
    {
        booksSearchModel->clear();
    }

    booksSearchModel = new QSqlTableModel(this, QSqlDatabase::database("main connection"));
    booksSearchModel->setTable("book");

    auto it = bookTableColumnNames.begin();
    for (int i = 0; i < booksSearchModel->columnCount(); ++i, ++it)
    {
        booksSearchModel->setHeaderData(i, Qt::Horizontal, it.key());
    }

    booksSearchModel->setSort(1, Qt::AscendingOrder); // 1 - sort by book name

    QString booksSearchModelFilter = ( ui->comboBox->currentText() == "все" ?
                                         QString("isbn LIKE '%%1%' OR booktitle LIKE '%%1%' "
                                                 "OR authorsnames LIKE '%%1%' OR cityofpublication LIKE '%%1%' "
                                                 "OR publisher LIKE '%%1%' OR yearofpublication LIKE '%%1%' "
                                                 "OR pagecount LIKE '%%1%' OR category LIKE '%%1%' "
                                                 "OR cost LIKE '%%1%'").arg(ui->lineEdit->text())
                                         : QString("%1 LIKE '%%2%'").arg(bookTableColumnNames.value(ui->comboBox->currentText())).arg(ui->lineEdit->text()) );
    booksSearchModel->setFilter(booksSearchModelFilter);
    booksSearchModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->tableView_2->setSelectionMode(QAbstractItemView::NoSelection);

    if (!booksSearchModel->select())
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
