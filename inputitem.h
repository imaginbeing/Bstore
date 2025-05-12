#ifndef INPUTITEM_H
#define INPUTITEM_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "sql.h"

namespace Ui {
class InputItem;
}

class InputItem : public QDialog
{
    Q_OBJECT
    enum DialogType { SUBCAT, CATEGORY } dialog_type;
    explicit InputItem(QWidget *parent, const QString &name, const int cat_id);
    explicit InputItem(QWidget *parent, const QString &name, const int cat_id, const int sub_id);
    ~InputItem();

public:
    static void setSubcat(QWidget *parent, QString &name, int &cat_id, bool *ok = nullptr);
    static void setCategory(QWidget *parent, QString &name, int &sub_id, bool *ok = nullptr);

private slots:
    void on_pushButton_ok_clicked();

    void on_comboBox_cat_currentIndexChanged(int index);

private:
    Ui::InputItem *ui;

signals:
    void send_name(const QString &name);
    void send_catalog(const int id);
    void send_subcat(const int id);

};

#endif // INPUTITEM_H
