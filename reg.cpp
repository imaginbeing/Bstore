#include "reg.h"
#include "ui_reg.h"

Reg::Reg(QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Reg)
{
    this->ui->setupUi(this);
    this->ui->widget_reg->hide();
    this->ui->radioButton_client->setChecked(true);
    this->setWindowTitle("Регистрация");
    this->setFixedSize(this->size());
}

Reg::~Reg() //деструктор
{
    delete this->ui;
}

void Reg::open() //переопределение открытия окна
{
    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);
    QDialog::open();
}

void Reg::openFromLogin() //открытие окна из окна логина
{
    QObject::connect(this, &QDialog::finished, this->parentWidget(), &QWidget::show);
    this->open();
}

void Reg::on_pushButton_continue_clicked() //нажатие кнопки продолжить регистрацию
{
    this->provider = this->ui->radioButton_provider->isChecked();
    this->ui->label_reg->setText(QString("Регистрация %1").arg(this->provider ? "оптового продавца" : "розничного покупателя"));
    this->ui->widget_start->hide();
    this->ui->widget_reg->show();
}

void Reg::on_pushButton_r_clicked() //нажатие на кнопку зарегистрироваться
{
    const QString login = this->ui->lineEdit_l->text();
    if (login.trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Введите логин");
        return;
    }
    if (login.trimmed().size() < 3)
    {
        QMessageBox::warning(this, "Ошибка", "Логин должен быть не менее 3 символов длиной");
        return;
    }
    if (login.contains(QRegExp("\\s")))
    {
        QMessageBox::warning(this, "Ошибка", "Логин не должен содержать пробелы");
        return;
    }

    QString name = this->ui->lineEdit_n->text();
    if (name.trimmed().isEmpty())
    {
        name = login;
    }

    const QString password = this->ui->lineEdit_p->text();
    if (password.trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Введите пароль");
        return;
    }
    if (password.trimmed().size() < 6)
    {
        QMessageBox::warning(this, "Ошибка", "Пароль должен быть не менее 6 символов длиной");
        return;
    }
    if (password.contains(QRegExp("\\s")))
    {
        QMessageBox::warning(this, "Ошибка", "Пароль не должен содержать пробелы");
        return;
    }

    const QString password2 = this->ui->lineEdit_p_2->text();
    if (password != password2)
    {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают");
        return;
    }

    const QString table = this->provider ? "provider" : "clients";
    QSqlQuery q(SQL::db());
    q.prepare(QString("SELECT id FROM public.%1 WHERE login = :l;").arg(table));
    q.bindValue(":l", login);
    q.exec();

    const bool exist = q.first();
    if (exist)
    {
        QMessageBox::warning(this, "Ошибка", "Такой пользователь уже существует!");
        return;
    }

    const QString admin = this->provider ? QString() : ", admin";
    const QString def = this->provider ? QString() : ", DEFAULT";
    q.prepare(QString("INSERT INTO public.%1 (id, login, password, name%2) VALUES (DEFAULT, :l, :p, :n%3);").arg(table, admin, def));
    q.bindValue(":l", login);
    q.bindValue(":p", password);
    q.bindValue(":n", name);
    q.exec();

    QMessageBox::information(this, "Регистрация", "Регистрация прошла успешно! Теперь вы можете войти в свой аккаунт.");
    emit this->send_login(login);
    this->accept();
}

