#ifndef PRODUCTFEATURES_H
#define PRODUCTFEATURES_H

#include <QDialog>
#include <QListWidgetItem>

#include "sql.h"
#include "featurechanger.h"

namespace Ui {
class ProductFeatures;
}

class ProductFeatures : public QDialog
{
    Q_OBJECT
    int id;

public:
    explicit ProductFeatures(const int id, QWidget *parent = nullptr);
    ~ProductFeatures();

private slots:
    void on_pushButton_add_clicked();
    void update_list();

    void on_pushButton_del_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ProductFeatures *ui;
};

#endif // PRODUCTFEATURES_H
