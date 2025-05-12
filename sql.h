#ifndef SQL_H
#define SQL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

namespace sql
{
    namespace set
    {
        const QString sql_name("Bstore");
        const QString sql_host("127.0.0.1");
        const QString sql_user("postgres");
        const QString sql_password("228");
        const int sql_port(5432);
    }
}

class SQL;
class SQLDestroy
{
    SQL *_db = nullptr;

public:
    ~SQLDestroy();
    void init(SQL *db) { this->_db = db; } //сеттер поинтера бд для автоматического удаления
};

class SQL : public QSqlDatabase
{
    Q_DISABLE_COPY(SQL)
    SQL() : QSqlDatabase() { } //конструктор
    SQL(const QSqlDatabase &db) : QSqlDatabase(db) { } //конструктор
    ~SQL() { } //деструктор

    static SQL *_db;
    static SQLDestroy dbd;
    friend class SQLDestroy;

public:
    static SQL &db();

};

#endif // SQL_H
