#ifndef PROVIDERPRODUCT_H
#define PROVIDERPRODUCT_H

#include <QDialog>
#include <QListWidgetItem>

#include "sql.h"
#include "productchanger.h"

namespace Ui {
class ProviderProduct;
}

class ProviderProduct : public QDialog
{
    Q_OBJECT
    int provider;

public:
    explicit ProviderProduct(const int id, QWidget *parent = nullptr);
    ~ProviderProduct();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_sup_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void reset_list();

private:
    Ui::ProviderProduct *ui;
};

#endif // PROVIDERPRODUCT_H
