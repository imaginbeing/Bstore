#include "storage.h"
#include "ui_storage.h"
// to tablewidget
Storage::Storage(const int provider, QWidget *parent) : //конструктор
    QDialog(parent), provider(provider),
    ui(new Ui::Storage)
{
    this->ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Склад");
    this->ui->listWidget->hide();

    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    if (this->provider)
    {
        ui->tableWidget->setColumnCount(3);// столбцы таблицы

        QStringList Columnlist;
        Columnlist.append("Название");
        Columnlist.append("Кол-во");
        Columnlist.append("Последняя поставка");

        ui->tableWidget->setHorizontalHeaderLabels(Columnlist);

        QSqlQuery q(SQL::db());
        q.prepare("SELECT id, name FROM public.product WHERE provider_id = :pid;");
        q.bindValue(":pid", this->provider);
        q.exec();

        while (q.next())
        {
            QSqlQuery q2(SQL::db());
            q2.prepare("SELECT amount, last_delivery FROM public.storage WHERE product_id = :pid;");
            const int product = q.value("id").toInt();
            q2.bindValue(":pid", product);
            q2.exec();
            const QString name = q.value("name").toString();



            int cur_row = 0;
            this->ui->tableWidget->setRowCount(cur_row+1);
            while (q2.next())
            {
                const int amount = q2.value("amount").toInt();
                const QDate date = q2.value("last_delivery").toDate();
                QString fullName = name;
                //fullName += QString(" Кол-во: %1 шт.").arg(amount);
                //fullName += QString(" Последняя поставка: %1").arg(date.isValid() ? date.toString(Qt::DefaultLocaleShortDate) : "-");

                //new QTableWidgetItem(fullName, this->ui->tableWidget);

                for (int i = 0; i < 3 ; i++ )
                {
                QTableWidgetItem * item = new QTableWidgetItem;
                ui->tableWidget->setItem(cur_row,i,item);
                }

                ui->tableWidget->item(cur_row,0)->setText(fullName);
                ui->tableWidget->item(cur_row,1)->setText(QString::number(amount));
                ui->tableWidget->item(cur_row,2)->setText(QString(date.isValid() ? date.toString(Qt::DefaultLocaleShortDate) : "-"));

                this->ui->tableWidget->resizeRowsToContents();
                this->ui->tableWidget->resizeColumnsToContents();
            }
            cur_row++;
        }

    }
    else
    {
        QSqlQuery q(SQL::db());
        q.exec("SELECT product_id, amount, last_delivery FROM public.storage;");


        ui->tableWidget->setColumnCount(4);// столбцы таблицы
        QStringList Columnlist;
        Columnlist.append("Имя");
        Columnlist.append("Поставщик");
        Columnlist.append("Кол-во");
        Columnlist.append("Последняя поставка");

        ui->tableWidget->setHorizontalHeaderLabels(Columnlist);

        int cur_row = 0;
        while (q.next())
        {
            const int product = q.value("product_id").toInt();
            const int amount = q.value("amount").toInt();
            const QDate date = q.value("last_delivery").toDate();
            QSqlQuery q2(SQL::db());
            q2.prepare("SELECT name, provider_id FROM public.product WHERE id = :id;");
            q2.bindValue(":id", product);
            q2.exec();
            q2.first();
            const QString name = q2.value("name").toString();
            const int provider = q2.value("provider_id").toInt();
            q2.prepare("SELECT name FROM public.provider WHERE id = :id;");
            q2.bindValue(":id", provider);
            q2.exec();
            q2.first();
            const QString provName = q2.value("name").toString();
            QString fullName = name;
            //fullName += QString(" (%1)").arg(provName);
            //fullName += QString(" Кол-во: %1 шт.").arg(amount);
            //fullName += QString(" Последняя поставка: %1").arg(date.isValid() ? date.toString(Qt::DefaultLocaleShortDate) : "-");
            //new QListWidgetItem(fullName, this->ui->listWidget);


            this->ui->tableWidget->setRowCount(cur_row+1);

            for (int i = 0; i < 4 ; i++ )
            {
            QTableWidgetItem * item = new QTableWidgetItem;
            ui->tableWidget->setItem(cur_row,i,item);
            }

            ui->tableWidget->item(cur_row,0)->setText(fullName);
            ui->tableWidget->item(cur_row,1)->setText(QString(provName));
            ui->tableWidget->item(cur_row,2)->setText(QString::number(amount));
            ui->tableWidget->item(cur_row,3)->setText(QString(date.isValid() ? date.toString(Qt::DefaultLocaleShortDate) : "-"));

            cur_row++;

        }

        this->ui->tableWidget->resizeRowsToContents();
        this->ui->tableWidget->resizeColumnsToContents();
    }
}

Storage::Storage(UserType ut, QWidget *parent) : //конструктор
    QDialog(parent), utype(ut),
    ui(new Ui::Storage)
{
    this->ui->setupUi(this);
    this->setFixedSize(this->size());
    this->ui->tableWidget->hide();

    QObject::connect(this->ui->listWidget, &QListWidget::itemDoubleClicked, this, &Storage::item_2clicked);
    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);

    QSqlQuery q(SQL::db());
    switch (this->utype)
    {
    case USER: Q_FALLTHROUGH();
    case ADMIN:
    {
        q.prepare("SELECT id, login, name FROM public.clients WHERE admin = :a;");
        const bool admin = this->utype;
        q.bindValue(":a", admin);
        q.exec();
        break;
    }
    case PROV:
    {
        q.exec("SELECT id, login, name FROM public.provider;");
    }
    }

    while (q.next())
    {
        const int id = q.value("id").toInt();
        const QString login = q.value("login").toString();
        const QString name = q.value("name").toString();

        QString fullName = QString("Логин: %1").arg(login);
        fullName += QString(" Имя: %1").arg(name);
        auto item = new QListWidgetItem(fullName, this->ui->listWidget);
        item->setData(Qt::UserRole, id);
    }
}

Storage::~Storage() //деструктор
{
    delete ui;
}

void Storage::openUsers(QWidget *parent) //окно покупателей
{
    auto dialog = new Storage(USER, parent);
    dialog->setWindowTitle("Покупатели");
    dialog->open();
}

void Storage::openProviders(QWidget *parent) //окно продавцов
{
    auto dialog = new Storage(PROV, parent);
    dialog->setWindowTitle("Продавцы");
    dialog->open();
}

void Storage::openAdmins(QWidget *parent) //окно админов
{
    auto dialog = new Storage(ADMIN, parent);
    dialog->setWindowTitle("Администраторы");
    dialog->open();
}

void Storage::item_2clicked(QListWidgetItem *item) //двойное нажатие по элементу листа
{
    if (this->utype == ADMIN) return;
    if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите удалить данного пользователя?") == QMessageBox::No) return;

    QSqlQuery q(SQL::db());
    q.prepare(QString("DELETE FROM public.%1 WHERE id = :id;").arg(this->utype == PROV ? "provider" : "clients"));
    q.bindValue(":id", item->data(Qt::UserRole));
    q.exec();

    QMessageBox::information(this, "Информация", "Пользователь успешно удален!");
}
