#ifndef REG_H
#define REG_H

#include <QDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QDebug>

#include "sql.h"

namespace Ui {
class Reg;
}

class Reg : public QDialog
{
    Q_OBJECT
    bool provider = false;

public:
    explicit Reg(QWidget *parent = nullptr);
    ~Reg();

public slots:
    void open() override;
    void openFromLogin();

private slots:
    void on_pushButton_continue_clicked();

    void on_pushButton_r_clicked();

private:
    Ui::Reg *ui;

signals:
    void send_login(const QString &login);
};

#endif // REG_H
