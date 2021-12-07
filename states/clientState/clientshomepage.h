#ifndef CLIENTSHOMEPAGE_H
#define CLIENTSHOMEPAGE_H

#include <QWidget>

namespace Ui {
class ClientsHomePage;
}

class ClientsHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsHomePage(QWidget *parent = nullptr);
    ~ClientsHomePage();

private:
    Ui::ClientsHomePage *ui;
};

#endif // CLIENTSHOMEPAGE_H
