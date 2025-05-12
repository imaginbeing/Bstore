#include "supply.h"
#include "ui_supply.h"

Supply::Supply(QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Supply)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Поставки");
    QObject::connect(this->ui->listWidget, &QListWidget::itemDoubleClicked, this, &Supply::item_dd);
    this->update_list();
}

Supply::Supply(const int provider, QWidget *parent) : //конструктор
    QDialog(parent), provider(provider),
    ui(new Ui::Supply)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Поставки");

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, name FROM public.product WHERE provider_id = :pid;");
    q.bindValue(":pid", this->provider);
    q.exec();
    while (q.next())
    {
        const int product = q.value("id").toInt();
        const QString name = q.value("name").toString();
        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT amount, approved, request_date, approve_date FROM public.supply WHERE product_id = :pid;");
        q2.bindValue(":pid", product);
        q2.exec();
        while (q2.next())
        {
            const int amount = q2.value("amount").toInt();
            const QDate req = q2.value("request_date").toDate();
            const QDate app = q2.value("approve_date").toDate();
            const QString appd = app.isValid() ? app.toString(Qt::DefaultLocaleShortDate) : "-";
            const QString itemName = name
                + QString(" кол-во: %1шт. запрос: %2 ответ: %3").arg(QString::number(amount), req.toString(Qt::DefaultLocaleShortDate), appd);
            auto item = new QListWidgetItem(itemName, this->ui->listWidget);
            const bool approved = q2.value("approved").toBool();
            if (approved) item->setBackground(Qt::green);
            else item->setBackground(Qt::white);
        }
    }
}

Supply::~Supply() //деструктор
{
    delete ui;
}

void Supply::update_list() //обновление листа
{
    this->ui->listWidget->clear();

    QSqlQuery q(SQL::db());
    q.exec("SELECT id, name FROM public.product;");
    while (q.next())
    {
        const int product = q.value("id").toInt();
        const QString name = q.value("name").toString();
        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT id, amount, approved, request_date, approve_date FROM public.supply WHERE product_id = :pid;");
        q2.bindValue(":pid", product);
        q2.exec();
        while (q2.next())
        {
            const int amount = q2.value("amount").toInt();
            const QDate req = q2.value("request_date").toDate();
            const QDate app = q2.value("approve_date").toDate();
            const QString appd = app.isValid() ? app.toString(Qt::DefaultLocaleShortDate) : "-";
            const QString itemName = name
                + QString(" кол-во: %1шт. запрос: %2 ответ: %3").arg(QString::number(amount), req.toString(Qt::DefaultLocaleShortDate), appd);
            auto item = new QListWidgetItem(itemName, this->ui->listWidget);
            item->setData(Qt::UserRole, q2.value("id"));
            const bool approved = q2.value("approved").toBool();
            if (approved) item->setBackground(Qt::green);
            else item->setBackground(Qt::white);
        }
    }
}

void Supply::item_dd(QListWidgetItem *item) //двойной клик по элементу листа для изменения
{
    QSqlQuery q(SQL::db());
    q.prepare("SELECT amount, approved, product_id FROM public.supply WHERE id = :id;");
    q.bindValue(":id", item->data(Qt::UserRole));
    q.exec();
    q.first();
    const bool approved = q.value("approved").toBool();
    if (!approved)
    {
        if (QMessageBox::question(this, "Поставка", "Вы хотите принять эту поставку?") == QMessageBox::No) return;
        const int product = q.value("product_id").toInt();
        const int amount = q.value("amount").toInt();

        q.prepare("UPDATE public.supply SET approved = true, approve_date = CURRENT_DATE WHERE id = :id;");
        q.bindValue(":id", item->data(Qt::UserRole));
        q.exec();

        q.prepare("SELECT id FROM public.storage WHERE product_id = :pid;");
        q.bindValue(":pid", product);
        q.exec();
        if (q.first())
        {
            const int storage = q.value("id").toInt();
            q.prepare("UPDATE public.storage SET amount = amount + :a, last_delivery = CURRENT_DATE WHERE id = :id;");
            q.bindValue(":a", amount);
            q.bindValue(":id", storage);
            q.exec();
        }
        else
        {
            q.prepare("INSERT INTO public.storage (id, product_id, amount, last_delivery) "
                      "VALUES (DEFAULT, :pid, :a, CURRENT_DATE);");
            q.bindValue(":pid", product);
            q.bindValue(":a", amount);
            q.exec();
        }
        QMessageBox::information(this, "Информация", "Поставка успешно обработана!");
    }

    this->update_list();
}
