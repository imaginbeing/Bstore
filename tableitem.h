#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QScrollArea>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>

#include "sql.h"

class TableItem : public QFrame
{
    Q_OBJECT

    QPushButton *button(const QString &text1, const int price, QWidget *parent);
    QPushButton *button(const QString &text, QWidget *parent, const bool bold);
    QPushButton *button(const QString &text, QWidget *parent, const double rate, const int comms, const int price);

public:
    TableItem(QWidget *parent = nullptr) : QFrame(parent) { } //конструктор
    TableItem *asCatalog(const int id, const QString &name);
    TableItem *asSubcat(const int id, const QString &name);
    TableItem *asProduct(const int product, const QString &name, const int price);
    TableItem *asReview(const int rate, const QString &review, const QString &username);
    TableItem *asCartItem(const int product, const int cart, const QString &name, const int price, const int amount);

signals:
    void send_catalog(const int id);
    void send_category(const int id);
    void send_subcat(const int id);
    void send_product(const int id);
    void send_cart(const int id);
    void send_name(const QString &name);

    void increase_cart(const int cart, const int size);
    void decrease_cart(const int cart, const int size);

private slots:
    void onCatalog();
    void onCategory();
    void onSubcat();
    void onProduct();
    void onCart();
    void onCartProd();
    void onCartSpin(int val);

};

#endif // TABLEITEM_H
