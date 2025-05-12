#include "sql.h"

SQL *SQL::_db = nullptr;
SQLDestroy SQL::dbd;

SQLDestroy::~SQLDestroy()
{ delete this->_db; } //деструктор

SQL &SQL::db() //геттер базы данных
{
    if (_db == nullptr)
    {
        using namespace sql::set;

        _db = new SQL(QSqlDatabase::addDatabase("QPSQL"));
        _db->setDatabaseName(sql_name);
        _db->setHostName(sql_host);
        _db->setUserName(sql_user);
        _db->setPassword(sql_password);
        _db->setPort(sql_port);
        _db->open();

        dbd.init(_db);
    }
    return *_db;
}
