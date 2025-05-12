#ifndef PRODUCTCHANGER_H
#define PRODUCTCHANGER_H

#include <QDialog>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

#include "sql.h"
#include "productfeatures.h"

namespace Ui {
class ProductChanger;
}

class ProductChanger : public QDialog
{
    Q_OBJECT
    int id;
    int provider;
    int cid = 1;
    int price = 0;
    QString name = QString();
    QString purp = QString();
    QString descr = QString();

    bool onStart = true;

public:
    explicit ProductChanger(const int provider, const int id = 0, QWidget *parent = nullptr);
    ~ProductChanger();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_name_clicked();

    void on_pushButton_price_clicked();

    void on_pushButton_purp_clicked();

    void on_pushButton_desc_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_feature_clicked();

private:
    Ui::ProductChanger *ui;
};

#endif // PRODUCTCHANGER_H
