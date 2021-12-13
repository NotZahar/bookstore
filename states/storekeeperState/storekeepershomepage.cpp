#include "storekeepershomepage.h"
#include "ui_storekeepershomepage.h"

StoreKeepersHomePage::StoreKeepersHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreKeepersHomePage)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &StoreKeepersHomePage::storeKeeperExitsFromHomePage);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &StoreKeepersHomePage::goToWarehouseButtonIsPushed);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &StoreKeepersHomePage::goToBooksButtonIsPushed);
}

StoreKeepersHomePage::~StoreKeepersHomePage()
{
    delete ui;
}

void StoreKeepersHomePage::displayEmployeeData(const QList<QVariant> &data)
{
    QString employeeDataQueryString = "SELECT employeeid, department, appointment, "
                                      "surname, uname, patronymic, birthdate, "
                                      "homeaddress, phone, email "
                                      "FROM employee WHERE email = '%1';";
    QSqlQuery employeeDataQuery(QSqlDatabase::database("main connection"));
    if (!employeeDataQuery.exec(employeeDataQueryString
                                 .arg(data.at(0).toString())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    if (employeeDataQuery.next())
    {
        ui->label_12->setText(employeeDataQuery.value("employeeid").toString());
        ui->label_13->setText(employeeDataQuery.value("department").toString());
        ui->label_14->setText(employeeDataQuery.value("appointment").toString());
        ui->label_15->setText(employeeDataQuery.value("surname").toString());
        ui->label_16->setText(employeeDataQuery.value("uname").toString());
        ui->label_17->setText(employeeDataQuery.value("patronymic").toString());
        ui->label_18->setText(employeeDataQuery.value("birthdate").toDate().toString("dd.MM.yyyy"));
        ui->label_19->setText(employeeDataQuery.value("homeaddress").toString());
        ui->label_20->setText(employeeDataQuery.value("phone").toString());
        ui->label_21->setText(employeeDataQuery.value("email").toString());
    }
}

void StoreKeepersHomePage::storeKeeperExitsFromHomePage(bool)
{
    emit storeKeeperExitedFromHomePage();
}

void StoreKeepersHomePage::goToWarehouseButtonIsPushed(bool)
{
    emit goToWarehouseButtonWasPushed();
}

void StoreKeepersHomePage::goToBooksButtonIsPushed(bool)
{
    emit goToBooksButtonWasPushed();
}
