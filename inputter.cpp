#include "inputter.h"
#include "ui_inputter.h"

Inputter::Inputter(DialogType dt, QWidget *parent) : //конструктор
    QDialog(parent), dialog_type(dt),
    ui(new Ui::Inputter)
{
    this->ui->setupUi(this);
    this->setInfo();
    this->setWindowTitle(this->info.title);

    int height;
    QSqlQuery q(SQL::db());
    switch (this->dialog_type)
    {
    case FEATURE:
        Q_FALLTHROUGH();
    case CATALOG:
    {
        this->ui->comboBox_cat->hide();
        this->ui->comboBox_sub->hide();
        this->ui->label_cat->hide();
        this->ui->label_sub->hide();
        height = 299;

        q.exec(QString("SELECT id, name FROM public.%1;").arg(this->info.table));
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            auto item = new QListWidgetItem(name, this->ui->listWidget);
            item->setData(Qt::UserRole, id);
        }
        break;
    }
    case SUBCAT:
    {
        this->ui->comboBox_sub->hide();
        this->ui->label_sub->hide();
        height = 346;

        this->ui->comboBox_cat->addItem("Все", 0);
        q.exec("SELECT id, name FROM public.catalog;");
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            this->ui->comboBox_cat->addItem(name, id);
        }
        break;
    }
    case CATEGORY:
        height = 393;
        this->ui->comboBox_cat->addItem("Все", 0);
        q.exec("SELECT id, name FROM public.catalog;");
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            this->ui->comboBox_cat->addItem(name, id);
        }
        break;
    }

    this->setFixedSize(this->width(), height);

    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);
}

Inputter::~Inputter() //деструктор
{
    delete this->ui;
}

void Inputter::setInfo() //сеттер текстовых полей
{
    switch (this->dialog_type)
    {
    case FEATURE:
    {
        this->info.title = "Товарные характеристики";
        this->info.table = "feature";
        this->info.question = "Вы уверены, что хотите удалить характеристику? Все товары, имеющие данную характеристику, потеряют информацию о ней безвозвратно!";

        this->info.item.title = "Новая характеристика";
        this->info.item.label = "Введите название новой характеристики:";
        this->info.item.emptyError = "Введите название характеристики";
        this->info.item.sizeError = "Название характеристики слишком длинное!";
        this->info.item.existError = "Такая характеристика уже существует!";
        this->info.item.oopsError = "Характеристика не добавлена, что-то пошло не так!";

        this->info.name = this->info.item;
        this->info.name.label = "Введите новое имя для характеристики:";
        this->info.name.existError = "Характеристика с таким именем уже существует!";
        break;
    }
    case CATALOG:
    {
        this->info.title = "Каталоги товаров";
        this->info.table = "catalog";
        this->info.question = "Вы уверены, что хотите удалить каталог? Все подкаталоги, категории и товары, принадлежащие данному каталогу, пропадут безвозвратно!";

        this->info.item.title = "Новый каталог";
        this->info.item.label = "Введите название нового каталога:";
        this->info.item.emptyError = "Введите название каталога";
        this->info.item.sizeError = "Название каталога слишком длинное!";
        this->info.item.existError = "Такой каталог уже существует!";
        this->info.item.oopsError = "Каталог не добавлен, что-то пошло не так!";
        this->info.item.id1Error = "Нельзя удалить основной каталог стройматериалов!";

        this->info.name = this->info.item;
        this->info.name.label = "Введите новое имя для каталога:";
        this->info.name.existError = "Каталог с таким именем уже существует!";
        break;
    }
    case SUBCAT:
    {
        this->info.title = "Подкаталоги товаров";
        this->info.table = "subcatalog";
        this->info.question = "Вы уверены, что хотите удалить подкаталог? Все категории и товары, принадлежащие данному подкаталогу, пропадут безвозвратно!";

        this->info.item.title = "Новый подкаталог";
        this->info.item.label = "Введите название нового подкаталога:";
        this->info.item.emptyError = "Введите название подкаталога";
        this->info.item.sizeError = "Название подкаталога слишком длинное!";
        this->info.item.existError = "Такой подкаталог уже существует!";
        this->info.item.oopsError = "Подкаталог не добавлен, что-то пошло не так!";
        this->info.item.id1Error = "Нельзя удалить основной подкаталог листовых материалов!";

        this->info.name = this->info.item;
        this->info.name.label = "Введите новое имя для подкаталога:";
        this->info.name.existError = "Подкаталог с таким именем уже существует!";
        break;
    }
    case CATEGORY:
    {
        this->info.title = "Категории товаров";
        this->info.table = "category";
        this->info.question = "Вы уверены, что хотите удалить категорию? Все товары, принадлежащие данной категории, пропадут безвозвратно!";

        this->info.item.title = "Новая категория";
        this->info.item.label = "Введите название новой категории:";
        this->info.item.emptyError = "Введите название категории";
        this->info.item.sizeError = "Название категории слишком длинное!";
        this->info.item.existError = "Такая категория уже существует!";
        this->info.item.oopsError = "Категория не добавлена, что-то пошло не так!";
        this->info.item.id1Error = "Нельзя удалить основную категорию гипсокартона!";

        this->info.name = this->info.item;
        this->info.name.label = "Введите новое имя для категории:";
        this->info.name.existError = "Категория с таким именем уже существует!";
        break;
    }
    }
}

void Inputter::openFeature(QWidget *parent) //создание объекта как характеристик
{
    auto dialog = new Inputter(FEATURE, parent);
    dialog->open();
}

void Inputter::openCatalog(QWidget *parent) //создание объекта как каталогов
{
    auto dialog = new Inputter(CATALOG, parent);
    dialog->open();
}

void Inputter::openSubcat(QWidget *parent) //создание объекта как подкаталогов
{
    auto dialog = new Inputter(SUBCAT, parent);
    dialog->open();
}

void Inputter::openCategory(QWidget *parent) //создание объекта как категоий
{
    auto dialog = new Inputter(CATEGORY, parent);
    dialog->open();
}

void Inputter::on_pushButton_add_clicked() //добавление нового элемента в список
{
    QString newItem = QString();
    int cat_id = this->ui->comboBox_cat->currentData().toInt();
    int sub_id = this->ui->comboBox_sub->currentData().toInt();
    do
    {
        bool fl;
        QString query = "SELECT id FROM public.%1 WHERE name = :n";
        switch (this->dialog_type)
        {
        case FEATURE:
            Q_FALLTHROUGH();
        case CATALOG:
            newItem = QInputDialog::getText(this, this->info.item.title, this->info.item.label, QLineEdit::Normal, newItem,
                                            &fl, Qt::MSWindowsFixedSizeDialogHint);
            break;
        case SUBCAT:
        {
            InputItem::setSubcat(this, newItem, cat_id, &fl);
            query += " AND catalog_id = :cid";
            break;
        }
        case CATEGORY:
            InputItem::setCategory(this, newItem, sub_id, &fl);
            query += " AND subcatalog_id = :sid";
            break;
        }
        query += ';';

        if (!fl) return;
        if (newItem.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", this->info.item.emptyError);
            continue;
        }
        if (newItem.size() > 128)
        {
            QMessageBox::warning(this, "Ошибка", this->info.item.sizeError);
            continue;
        }

        QSqlQuery q(SQL::db());
        q.prepare(query.arg(this->info.table));
        q.bindValue(":n", newItem);
        if (this->dialog_type == SUBCAT) q.bindValue(":cid", cat_id);
        if (this->dialog_type == CATEGORY) q.bindValue(":sid", sub_id);
        q.exec();

        const bool exist = q.first();
        if (exist)
        {
            QMessageBox::warning(this, "Ошибка", this->info.item.existError);
            continue;
        }
        break;
    }
    while (true);

    QString columns = "(id%1, name)";
    QString values = "(DEFAULT%1, :n)";
    switch (this->dialog_type)
    {
    case FEATURE:
        Q_FALLTHROUGH();
    case CATALOG:
        columns = columns.arg(QString());
        values = values.arg(QString());
        break;
    case SUBCAT:
        columns = columns.arg(", catalog_id");
        values = values.arg(", :cid");
        break;
    case CATEGORY:
        columns = columns.arg(", subcatalog_id");
        values = values.arg(", :sid");
        break;
    }

    QSqlQuery q(SQL::db());
    q.prepare(QString("INSERT INTO public.%1 %2 VALUES %3;").arg(this->info.table, columns, values));
    qDebug() << QString("INSERT INTO public.%1 %2 VALUES %3;").arg(this->info.table, columns, values);
    q.bindValue(":cid", cat_id);
    q.bindValue(":sid", sub_id);
    q.bindValue(":n", newItem);
    q.exec();

    switch (this->dialog_type)
    {
    case FEATURE:
        Q_FALLTHROUGH(); // следующий  case
    case CATALOG:
    {
        QString query = "SELECT id FROM public.%1 WHERE name = :n;";
        q.prepare(query.arg(this->info.table));
        q.bindValue(":n", newItem);
        q.exec();

        if (!q.first())
        {
            QMessageBox::warning(this, "Ошибка", this->info.item.oopsError);
            return;
        }
        const int id = q.value("id").toInt();
        auto item = new QListWidgetItem(newItem, this->ui->listWidget);
        item->setData(Qt::UserRole, id);
        break;
    }
    case SUBCAT:
        this->ui->comboBox_cat->setCurrentIndex(0);
        for (int i = 0; i < this->ui->comboBox_cat->count(); ++i)
        {
            if (cat_id == this->ui->comboBox_cat->itemData(i).toInt())
            {
                this->ui->comboBox_cat->setCurrentIndex(i);
            }
        }
        break;
    case CATEGORY:
        this->ui->comboBox_cat->setCurrentIndex(-1);
        this->ui->comboBox_cat->setCurrentIndex(0);
        for (int i = 0; i < this->ui->comboBox_sub->count(); ++i)
        {
            if (sub_id == this->ui->comboBox_sub->itemData(i).toInt())
            {
                this->ui->comboBox_sub->setCurrentIndex(i);
            }
        }
        break;
    }
}

void Inputter::on_pushButton_del_clicked() //удаление выбранного элемента из списка
{
    if (this->ui->listWidget->currentRow() < 0) return;
    const int id = this->ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
    if(id == 1)
    {
        switch (this->dialog_type)
        {
        case FEATURE: break;
        case CATALOG:
            Q_FALLTHROUGH();
        case SUBCAT:
            Q_FALLTHROUGH();
        case CATEGORY:
            QMessageBox::warning(this, "Ошибка", this->info.item.id1Error);
            return;
        }
    }
    if (QMessageBox::question(this, "Предупреждение", this->info.question) == QMessageBox::No)
    {
        return;
    }

    QSqlQuery q(SQL::db());
    q.prepare(QString("DELETE FROM public.%1 WHERE id = :id;").arg(this->info.table));
    q.bindValue(":id", id);
    q.exec();

    this->ui->listWidget->takeItem(this->ui->listWidget->currentRow());
}

void Inputter::on_listWidget_itemDoubleClicked(QListWidgetItem *item) //изменение объекта, путем двойного нажатия по нему
{
    QString name = item->text();
    int cat_id = this->ui->comboBox_cat->currentData().toInt();
    if (this->dialog_type == SUBCAT && !cat_id)
    {
        QSqlQuery q(SQL::db());
        q.prepare("SELECT catalog_id FROM public.subcatalog WHERE id = :id;");
        q.bindValue(":id", item->data(Qt::UserRole));
        q.exec();
        q.first();
        cat_id = q.value("catalog_id").toInt();
    }
    int ocat_id = cat_id;
    int sub_id = this->ui->comboBox_sub->currentData().toInt();
    if (this->dialog_type == CATEGORY && !sub_id)
    {
        QSqlQuery q(SQL::db());
        q.prepare("SELECT subcatalog_id FROM public.category WHERE id = :id;");
        q.bindValue(":id", item->data(Qt::UserRole));
        q.exec();
        q.first();
        sub_id = q.value("subcatalog_id").toInt();
    }
    int osub_id = sub_id;
    bool old_id;
    bool old_name;
    do
    {
        bool fl;
        QString query = "SELECT id FROM public.%1 WHERE name = :n";
        switch (this->dialog_type)
        {
        case FEATURE: Q_FALLTHROUGH();
        case CATALOG:
            name = QInputDialog::getText(this, "Новое имя", this->info.name.label, QLineEdit::Normal, name,
                                            &fl, Qt::MSWindowsFixedSizeDialogHint);
            break;
        case SUBCAT:
            InputItem::setSubcat(this, name, cat_id, &fl);
            query += " AND catalog_id = :cid";
            break;
        case CATEGORY:
            InputItem::setCategory(this, name, sub_id, &fl);
            query += " AND subcatalog_id = :sid";
            break;
        }
        query += ';';

        if (!fl) return;
        switch (this->dialog_type)
        {
        case FEATURE: break;
        case CATALOG: break;
        case SUBCAT:
            fl = cat_id == ocat_id;
            break;
        case CATEGORY:
            fl = sub_id == osub_id;
            break;
        }
        if (fl && name == item->text()) return;
        old_id = fl;
        old_name = name == item->text();

        if (name.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", this->info.name.emptyError);
            continue;
        }
        if (name.size() > 128)
        {
            QMessageBox::warning(this, "Ошибка", this->info.name.sizeError);
            continue;
        }

        QSqlQuery q(SQL::db());
        q.prepare(query.arg(this->info.table));
        q.bindValue(":n", name);
        q.bindValue(":cid", cat_id);
        q.bindValue(":sid", sub_id);
        q.exec();

        const bool exist = q.first();
        if (exist)
        {
            QMessageBox::warning(this, "Ошибка", this->info.name.existError);
            continue;
        }
        break;
    }
    while (true);

    QString query = QString("UPDATE public.%1 SET %2 WHERE id = :id;").arg(this->info.table);
    switch (this->dialog_type)
    {
    case FEATURE: Q_FALLTHROUGH();
    case CATALOG:
        query = query.arg("name = :n");
        break;
    case SUBCAT:
    {
        QStringList temp;
        if (!old_name) temp << "name = :n";
        if (!old_id) temp << "catalog_id = :cid";
        query = query.arg(temp.join(", "));
        break;
    }
    case CATEGORY:
    {
        QStringList temp;
        if (!old_name) temp << "name = :n";
        if (!old_id) temp << "subcatalog_id = :sid";
        query = query.arg(temp.join(", "));
        break;
    }
    }

    const int id = item->data(Qt::UserRole).toInt();
    QSqlQuery q(SQL::db());
    q.prepare(query);
    q.bindValue(":n", name);
    q.bindValue(":cid", cat_id);
    q.bindValue(":sid", sub_id);
    q.bindValue(":id", id);
    q.exec();

    item->setText(name);
    switch (this->dialog_type)
    {
    case FEATURE: break;
    case CATALOG: break;
    case SUBCAT:
        this->ui->comboBox_cat->setCurrentIndex(0);
        for (int i = 0; i < this->ui->comboBox_cat->count(); ++i)
        {
            if (cat_id == this->ui->comboBox_cat->itemData(i).toInt())
            {
                this->ui->comboBox_cat->setCurrentIndex(i);
            }
        }
        break;
    case CATEGORY:
        this->ui->comboBox_cat->setCurrentIndex(-1);
        this->ui->comboBox_cat->setCurrentIndex(0);
        for (int i = 0; i < this->ui->comboBox_sub->count(); ++i)
        {
            if (sub_id == this->ui->comboBox_sub->itemData(i).toInt())
            {
                this->ui->comboBox_sub->setCurrentIndex(i);
            }
        }
        break;
    }
}

void Inputter::on_comboBox_cat_currentIndexChanged(int index) //изменен индекс комбобокса
{
    if (index < 0) return;
    const int id = this->ui->comboBox_cat->currentData().toInt();
    QSqlQuery q(SQL::db());
    QString query = "SELECT id, name FROM public.subcatalog";
    if (id)
    {
        query += " WHERE catalog_id = :cid";
    }
    query += ';';
    q.prepare(query);
    if (id)
    {
        q.bindValue(":cid", id);
    }
    q.exec();
    if (this->dialog_type == SUBCAT)
    {
        this->ui->listWidget->clear();
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            auto item = new QListWidgetItem(name, this->ui->listWidget);
            item->setData(Qt::UserRole, id);
        }
    }
    if (this->dialog_type == CATEGORY)
    {
        this->ui->comboBox_sub->clear();
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            this->ui->comboBox_sub->addItem(name, id);
        }
    }
}


void Inputter::on_comboBox_sub_currentIndexChanged(int index) //изменение индекса комбобокса
{
    if (index < 0) return;
    const int id = this->ui->comboBox_sub->currentData().toInt();
    QSqlQuery q(SQL::db());
    QString query = "SELECT id, name FROM public.category";
    if (id)
    {
        query += " WHERE subcatalog_id = :sid";
    }
    query += ';';
    q.prepare(query);
    if (id)
    {
        q.bindValue(":sid", id);
    }
    q.exec();

    this->ui->listWidget->clear();
    while (q.next())
    {
        const int id = q.value("id").toInt();
        const QString name = q.value("name").toString();
        auto item = new QListWidgetItem(name, this->ui->listWidget);
        item->setData(Qt::UserRole, id);
    }
}

