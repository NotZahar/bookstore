#include "dpoperatorshomepage.h"
#include "ui_dpoperatorshomepage.h"

DPOperatorsHomePage::DPOperatorsHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DPOperatorsHomePage)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &DPOperatorsHomePage::operatorExitsFromHomePage);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &DPOperatorsHomePage::goToDPButtonIsPushed);
}

DPOperatorsHomePage::~DPOperatorsHomePage()
{
    delete ui;
}

void DPOperatorsHomePage::displayDPOperatorData(const QList<QVariant> &data)
{
    QString DPOperatorDataQueryString = "SELECT employeeid, appointment, "
                                        "surname, uname, patronymic, birthdate, "
                                        "phone, email "
                                        "FROM employee WHERE email = '%1';";
    QSqlQuery DPOperatorDataQuery(QSqlDatabase::database("main connection"));
    if (!DPOperatorDataQuery.exec(DPOperatorDataQueryString
                                 .arg(data.at(0).toString())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    if (DPOperatorDataQuery.next())
    {
        ui->label_10->setText(DPOperatorDataQuery.value("employeeid").toString());
        ui->label_11->setText(DPOperatorDataQuery.value("appointment").toString());
        ui->label_12->setText(DPOperatorDataQuery.value("surname").toString());
        ui->label_13->setText(DPOperatorDataQuery.value("uname").toString());
        ui->label_14->setText(DPOperatorDataQuery.value("patronymic").toString());
        ui->label_15->setText(DPOperatorDataQuery.value("birthdate").toDate().toString("dd.MM.yyyy"));
        ui->label_16->setText(DPOperatorDataQuery.value("phone").toString());
        ui->label_17->setText(DPOperatorDataQuery.value("email").toString());
    }
}

void DPOperatorsHomePage::operatorExitsFromHomePage(bool)
{
    emit operatorExitedFromHomePage();
}

void DPOperatorsHomePage::goToDPButtonIsPushed(bool)
{
    emit operatorWantedToGoToDP(ui->comboBox->currentText());
}
