#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include "reg.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_l_clicked();

    void on_pushButton_r_clicked();

private:
    Ui::Login *ui;

signals:
    void send_id(int id);
    void send_admin(bool admin);
    void send_provider();

};

#endif // LOGIN_H
