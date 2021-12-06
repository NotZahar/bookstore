#ifndef CLIENTSIGNUP_H
#define CLIENTSIGNUP_H

#include <QWidget>

namespace Ui {
class ClientSignUp;
}

class ClientSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit ClientSignUp(QWidget *parent = nullptr);
    ~ClientSignUp();

    void clearView();

private:
    Ui::ClientSignUp *ui;
};

#endif // CLIENTSIGNUP_H
