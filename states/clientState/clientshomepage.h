#ifndef CLIENTSHOMEPAGE_H
#define CLIENTSHOMEPAGE_H

#include <QWidget>
#include <QList>
#include <QVariant>

namespace Ui {
class ClientsHomePage;
}

class ClientsHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsHomePage(QWidget *parent = nullptr);
    ~ClientsHomePage();

    void displayClientData(const QList<QVariant> &data);

signals:
    void clientWantedToShop();
    void clientExitedFromHomePage();

private:
    Ui::ClientsHomePage *ui;
};

#endif // CLIENTSHOMEPAGE_H
