#ifndef BSTORE_H
#define BSTORE_H

#include <QMainWindow>

#include "sql.h"
#include "login.h"
#include "reg.h"
#include "inputter.h"
#include "providerproduct.h"
#include "supply.h"
#include "storage.h"
#include "tableitem.h"
#include "product.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Bstore; }
QT_END_NAMESPACE

class Bstore : public QMainWindow
{
    Q_OBJECT
    int id = 0;
    bool admin = false;
    bool provider = false;

    int cat_id = 1;
    enum TableType { CATALOG, SUBCATALOG, FROMSUB, FROMCAT, CART } ttype = CATALOG;

public:
    Bstore(QWidget *parent = nullptr);
    ~Bstore();

private:
    Ui::Bstore *ui;
    void clearLayout(QLayout *l);

private slots:
    void callLogin();
    void callReg();
    void callOut();
    void afterLogin();

    void set_id(int id) { this->id = id; } //сеттер индекса пользователя
    void set_admin(bool admin);
    void set_provider();
    void createCategory(const int subcat, const int category = 0);

    void on_pushButton_prod_clicked();
    void on_pushButton_sup_clicked();
    void on_pushButton_supply_clicked();
    void on_pushButton_storage_clicked();
    void on_pushButton_str_clicked();

    void setTableAsCatalog();
    void setTableAsCart();
    void setTableAsSubcat(const int catalog);
    void setTableFromSubcat(const int subcat);
    void setTableFromCategory(const int category);
    void on_pushButton_back_clicked();

    void categoryChanged();
    void callProduct(const int product);
    void addToCart(const int product);

    void cartIncreaser(const int cart, const int size);
    void cartDecreaser(const int cart, const int size);

    void changeName();
    void on_pushButton_buy_clicked();
};
#endif // BSTORE_H
