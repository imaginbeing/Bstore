#ifndef SUPPLY_H
#define SUPPLY_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

#include "sql.h"

namespace Ui {
class Supply;
}

class Supply : public QDialog
{
    Q_OBJECT
    int provider = 0;

public:
    explicit Supply(QWidget *parent = nullptr);
    explicit Supply(const int provider, QWidget *parent = nullptr);
    ~Supply();

private:
    Ui::Supply *ui;

private slots:
    void item_dd(QListWidgetItem *item);
    void update_list();

};

#endif // SUPPLY_H
