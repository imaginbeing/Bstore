#ifndef STORAGE_H
#define STORAGE_H

#include <QDialog>
#include <QDate>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>
#include <QAbstractItemView>

#include "sql.h"

namespace Ui {
class Storage;
}

class Storage : public QDialog
{
    Q_OBJECT
    int provider = 0;
    int admin = 0;
    enum UserType { USER, ADMIN, PROV } utype;
    explicit Storage(UserType ut, QWidget *parent = nullptr);

public:
    explicit Storage(QWidget *parent = nullptr) : Storage(0, parent) { } //конструктор
    explicit Storage(const int provider, QWidget *parent = nullptr);
    ~Storage();

    static void openUsers(QWidget *parent = nullptr);
    static void openProviders(QWidget *parent = nullptr);
    static void openAdmins(QWidget *parent = nullptr);

private:
    Ui::Storage *ui;

private slots:
    //void item_2clicked(QTableWidgetItem *item);
    void item_2clicked(QListWidgetItem *item);
};

#endif // STORAGE_H
