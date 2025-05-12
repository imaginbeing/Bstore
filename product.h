#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDialog>
#include <QGridLayout>

#include "sql.h"
#include "tableitem.h"

namespace Ui {
class Product;
}

class Product : public QDialog
{
    Q_OBJECT
    enum UType { ANON, USER, ADMIN, PROVIDER } const utype;
    explicit Product(const int id, const int user, const UType ut, QWidget *parent = nullptr);
    ~Product();

    const int id;
    const int user;

public:
    static void callAsAnon(const int id, QWidget *parent);
    static void callAsUser(const int id, const int user, QWidget *parent);
    static void callAsAdmin(const int id, const int user, QWidget *parent);
    static void callAsProv(const int id, const int user, QWidget *parent);

private:
    Ui::Product *ui;
    void setReviews();
    void addToCart(const int amount);

private slots:
    void callAgain(const int product);

    void on_pushButton_review_clicked();
    void on_pushButton_leftRev_clicked(bool checked);
    void on_pushButton_buy_clicked();
    void addToCart();
};

#endif // PRODUCT_H
