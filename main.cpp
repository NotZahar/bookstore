#include <QApplication>
#include <QIcon>

#include "statemanager.h"
#include "bookstore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(QPixmap("./images/icon.ico")));
    StateManager stateManager(Bookstore::states::entrance);
    QSqlDatabase dataBaseConnection;
    Bookstore::connectionToDataBase(dataBaseConnection);

    return a.exec();
}
