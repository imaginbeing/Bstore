#include "productchanger.h"
#include "ui_productchanger.h"

ProductChanger::ProductChanger(const int provider, const int id, QWidget *parent) : //конструктор
    QDialog(parent), id(id), provider(provider),
    ui(new Ui::ProductChanger)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedHeight(this->height());
    this->setWindowTitle("Товар");

    if (this->id)
    {
        this->ui->pushButton_add->hide();
        QSqlQuery q(SQL::db());
        q.prepare("SELECT * FROM public.product WHERE id = :id;");
        q.bindValue(":id", this->id);
        q.exec();
        if (q.first())
        {
            QSqlQuery q2(SQL::db());
            q2.exec("SELECT id, name FROM public.category;");
            const int cat_id = q.value("category_id").toInt();
            while (q2.next())
            {
                const int id = q2.value("id").toInt();
                const QString name = q2.value("name").toString();
                this->ui->comboBox->addItem(name, id);
                if (cat_id == id)
                {
                    this->ui->comboBox->setCurrentIndex(this->ui->comboBox->count() - 1);
                }
            }
            const int price = q.value("price").toInt();
            this->price = price;
            this->ui->label_price->setText(QString("Цена: %1 руб.").arg(price));
            this->ui->label_price->setToolTip(QString("%1 руб.").arg(price));
            const QString name = q.value("name").toString();
            this->name = name;
            this->ui->label_name->setText(QString("Название: %1").arg(name));
            this->ui->label_name->setToolTip(QString("%1").arg(name));
            const QString purp = q.value("purpose").toString();
            this->purp = purp;
            this->ui->label_purp->setToolTip(purp);
            const QString descr = q.value("description").toString();
            this->descr = descr;
            this->ui->label_descr->setToolTip(descr);
        }
    }
    else
    {
        this->ui->pushButton_feature->hide();
        QSqlQuery q(SQL::db());
        q.exec("SELECT id, name FROM public.category;");
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            this->ui->comboBox->addItem(name, id);
        }
    }

    this->onStart = !this->onStart;
}

ProductChanger::~ProductChanger() //деструктор
{
    delete ui;
}

void ProductChanger::on_comboBox_currentIndexChanged(int index) //изменение индекса комбобокса
{
    if (this->onStart) return;
    if (index < 0) return;
    if (!this->id)
    {
        this->cid = this->ui->comboBox->currentData().toInt();
        return;
    }
    if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите изменить категорию товару?") == QMessageBox::No)
    {
        return;
    }

    QSqlQuery q(SQL::db());
    q.prepare("UPDATE public.product SET category_id = :cid WHERE id = :id;");
    q.bindValue(":cid", this->ui->comboBox->currentData());
    q.bindValue(":id", this->id);
    q.exec();
    QMessageBox::information(this, "Информация", "Категория успешно изменена!");
}

void ProductChanger::on_pushButton_name_clicked() //нажатие на кнопку изменения имени
{
    QString newName;
    do
    {
        bool fl;
        newName = QInputDialog::getText(this, "Имя", "Изменить имя", QLineEdit::Normal, this->name,
                                        &fl, Qt::MSWindowsFixedSizeDialogHint);
        if (!fl) return;
        if (newName == this->name) return;
        if (newName.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Имя не должно быть пустым!");
            continue;
        }
        if (newName.size() > 128)
        {
            QMessageBox::warning(this, "Ошибка", "Имя не должно быть длиной больше 128 символов!");
            continue;
        }

        QSqlQuery q(SQL::db());
        q.prepare("SELECT id FROM public.product WHERE name = :n;");
        q.bindValue(":n", newName);
        q.exec();
        const bool exist = q.first();
        if (exist)
        {
            QMessageBox::warning(this, "Ошибка", "Такое имя занято!");
            continue;
        }
        break;
    }
    while (true);

    if (this->id)
    {
        if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите изменить название товара?") == QMessageBox::No)
        {
            return;
        }
        QSqlQuery q(SQL::db());
        q.prepare("UPDATE public.product SET name = :n WHERE id = :id;");
        q.bindValue(":n", newName);
        q.bindValue(":id", this->id);
        q.exec();
        QMessageBox::information(this, "Информация", "Название успешно изменено!");
    }
    this->name = newName;
    this->ui->label_name->setText(QString("Название: %1").arg(this->name));
    this->ui->label_name->setToolTip(QString("%1").arg(this->name));
    if (!this->id && this->ui->label_name->text().at(0) != '*')
        this->ui->label_name->setText(this->ui->label_name->text().prepend('*'));
}

void ProductChanger::on_pushButton_price_clicked() //нижатие на кнопку изменения цены
{
    int newPrice;
    do
    {
        bool fl;
        newPrice = QInputDialog::getInt(this, "Цена", "Изменить цену", this->price, 0, 999999, 1,
                                        &fl, Qt::MSWindowsFixedSizeDialogHint);
        if (!fl) return;
        if (newPrice == this->price) return;
        break;
    }
    while (true);

    if (this->id)
    {
        if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите изменить цену товара?") == QMessageBox::No)
        {
            return;
        }
        QSqlQuery q(SQL::db());
        q.prepare("UPDATE public.product SET price = :p WHERE id = :id;");
        q.bindValue(":p", newPrice);
        q.bindValue(":id", this->id);
        q.exec();
        QMessageBox::information(this, "Информация", "Цена успешно изменена!");
    }
    this->price = newPrice;
    this->ui->label_price->setText(QString("Цена: %1 руб.").arg(this->price));
    this->ui->label_price->setToolTip(QString("%1 руб.").arg(this->price));
    if (!this->id && this->ui->label_price->text().at(0) != '*')
        this->ui->label_price->setText(this->ui->label_price->text().prepend('*'));
}

void ProductChanger::on_pushButton_purp_clicked() //нажатие на кнопку изменения назначения
{
    QString newPurp;
    do
    {
        bool fl;
        newPurp = QInputDialog::getMultiLineText(this, "Назначение товара", "Изменить назначение товара", this->purp,
                                                 &fl, Qt::MSWindowsFixedSizeDialogHint);
        if (!fl) return;
        if (newPurp == this->purp) return;
        if (newPurp.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Назначение не должно быть пустым!");
            continue;
        }
        if (newPurp.size() > 128)
        {
            QMessageBox::warning(this, "Ошибка", "Назначение не должно быть длиной больше 128 символов!");
            continue;
        }
        break;
    }
    while (true);

    if (this->id)
    {
        if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите изменить назначение товара?") == QMessageBox::No)
        {
            return;
        }
        QSqlQuery q(SQL::db());
        q.prepare("UPDATE public.product SET purpose = :p WHERE id = :id;");
        q.bindValue(":p", newPurp);
        q.bindValue(":id", this->id);
        q.exec();
        QMessageBox::information(this, "Информация", "Назначение успешно изменено!");
    }
    else if (this->ui->label_purp->text().at(0) != '*')
        this->ui->label_purp->setText(this->ui->label_purp->text().prepend('*'));
    this->purp = newPurp;
    this->ui->label_purp->setToolTip(this->purp);
}

void ProductChanger::on_pushButton_desc_clicked() //нажатие на кнопку изменения описания
{
    QString newDesc;
    do
    {
        bool fl;
        newDesc = QInputDialog::getMultiLineText(this, "Описание товара", "Изменить описание товара", this->descr,
                                                 &fl, Qt::MSWindowsFixedSizeDialogHint);
        if (!fl) return;
        if (newDesc == this->descr) return;
        if (newDesc.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Описание не должно быть пустым!");
            continue;
        }
        if (newDesc.size() > 8192)
        {
            QMessageBox::warning(this, "Ошибка", "Описание не должно быть длиной больше 8192 символов!");
            continue;
        }
        break;
    }
    while (true);

    if (this->id)
    {
        if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите изменить описание товара?") == QMessageBox::No)
        {
            return;
        }
        QSqlQuery q(SQL::db());
        q.prepare("UPDATE public.product SET description = :d WHERE id = :id;");
        q.bindValue(":d", newDesc);
        q.bindValue(":id", this->id);
        q.exec();
        QMessageBox::information(this, "Информация", "описание успешно изменено!");
    }
    else if (this->ui->label_descr->text().at(0) != '*')
        this->ui->label_descr->setText(this->ui->label_descr->text().prepend('*'));
    this->descr = newDesc;
    this->ui->label_descr->setToolTip(this->descr);
}

void ProductChanger::on_pushButton_add_clicked() //нажатие на кнопку добавления
{
    if (!this->price)
    {
        QMessageBox::warning(this, "Ошибка", "Цена должна быть больше 0!");
        return;
    }
    if (this->name.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Придумайте название новому товару!");
        return;
    }
    if (this->purp.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Не указано назначение товара!");
        return;
    }
    if (this->descr.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Не указано описание товара!");
        return;
    }

    QSqlQuery q(SQL::db());
    q.prepare("INSERT INTO public.product (id, provider_id, category_id, name, description, purpose, price) " \
              "VALUES (DEFAULT, :pid, :cid, :n, :d, :pur, :pr);");
    q.bindValue(":pid", this->provider);
    q.bindValue(":cid", this->cid);
    q.bindValue(":n", this->name);
    q.bindValue(":d", this->descr);
    q.bindValue(":pur", this->purp);
    q.bindValue(":pr", this->price);
    q.exec();
    QMessageBox::information(this, "Информация", "Новый товар добавлен!");
    this->accept();
}


void ProductChanger::on_pushButton_feature_clicked() //нажатие на кнопку характеристик
{
    auto dialog = new ProductFeatures(this->id, this);
    dialog->open();
}

