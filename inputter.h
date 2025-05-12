#ifndef INPUTTER_H
#define INPUTTER_H

#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QListWidgetItem>

#include "inputitem.h"

namespace Ui {
class Inputter;
}

class Inputter : public QDialog
{
    Q_OBJECT
    enum DialogType { FEATURE, CATALOG, SUBCAT, CATEGORY } dialog_type;
    explicit Inputter(DialogType dt, QWidget *parent = nullptr);
    ~Inputter();

    struct
    {
        QString title;
        QString table;
        QString question;

        struct
        {
            QString title;
            QString label;
            QString emptyError;
            QString sizeError;
            QString existError;
            QString oopsError;
            QString id1Error;
        } item, name;

    } info;

    void setInfo();

public:
    static void openFeature(QWidget *parent = nullptr);
    static void openCatalog(QWidget *parent = nullptr);
    static void openSubcat(QWidget *parent = nullptr);
    static void openCategory(QWidget *parent = nullptr);

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_comboBox_cat_currentIndexChanged(int index);

    void on_comboBox_sub_currentIndexChanged(int index);

private:
    Ui::Inputter *ui;
};

#endif // INPUTTER_H
