#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Вход");
    this->setFixedSize(this->size());

    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);
}

Login::~Login() //деструктор
{
    delete ui;
}

void Login::on_pushButton_l_clicked() //нажатие кнопки входа
{
    const QString login = this->ui->lineEdit_l->text();
    const QString password = this->ui->lineEdit_p->text();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, admin FROM public.clients WHERE login = :l AND password = :p");
    q.bindValue(":l", login);
    q.bindValue(":p", password);
    q.exec();

    if (q.first())
    {
        QMessageBox::information(this, "Вход", "Вход выполнен успешно!");

        const int id = q.value("id").toInt();
        const bool admin = q.value("admin").toBool();

        emit this->send_admin(admin);
        emit this->send_id(id);

        this->accept();
        return;
    }

    q.prepare("SELECT id FROM public.provider WHERE login = :l AND password = :p");
    q.bindValue(":l", login);
    q.bindValue(":p", password);
    q.exec();

    if (!q.first())
    {
        QMessageBox::warning(this, "Ошибка", "Логин и/или пароль введены неверно!");
        return;
    }
    QMessageBox::information(this, "Вход", "Вход выполнен успешно!");

    const int id = q.value("id").toInt();

    emit this->send_provider();
    emit this->send_id(id);

    this->accept();
}

void Login::on_pushButton_r_clicked() //нажатие кнопки регистрации
{
    auto dialog = new Reg(this);
    QObject::connect(dialog, &Reg::send_login, this->ui->lineEdit_l, &QLineEdit::setText);
    dialog->openFromLogin();
    this->hide();
    this->ui->lineEdit_l->clear();
    this->ui->lineEdit_p->clear();
}

