#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

struct Bookstore
{
    enum states : int
    {
        entrance
    };

    enum users : int
    {
        impossibleUserRole,
        administrator,
        dpoperator,
        storekeeper,
        client
    };

    static void connectionToDataBase(QSqlDatabase &dbconnection)
    {
        dbconnection = QSqlDatabase::addDatabase("QMYSQL", "main connection");
        dbconnection.setHostName("localhost");
        dbconnection.setDatabaseName("bookshop");
        dbconnection.setUserName("root");
        dbconnection.setPassword("4321");
        if(!dbconnection.open())
        {
            QMessageBox::warning(nullptr, "Соединение с базой данных не установлено", dbconnection.lastError().text());
        }
    }
};

#endif // BOOKSTORE_H
