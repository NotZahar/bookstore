#ifndef CLIENTSSHOPPAGE_H
#define CLIENTSSHOPPAGE_H

#include <QWidget>

namespace Ui {
class ClientsShopPage;
}

class ClientsShopPage : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsShopPage(QWidget *parent = nullptr);
    ~ClientsShopPage();

signals:
    void backFromClientShopWasChosen();

private:
    Ui::ClientsShopPage *ui;
};

#endif // CLIENTSSHOPPAGE_H
