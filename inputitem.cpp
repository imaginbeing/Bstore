#include "inputitem.h"
#include "ui_inputitem.h"

InputItem::InputItem(QWidget *parent, const QString &name, const int cat_id) : //конструктор для подкаталога
    QDialog(parent), dialog_type(SUBCAT),
    ui(new Ui::InputItem)
{
    ui->setupUi(this);

    this->ui->label_sub->hide();
    this->ui->comboBox_sub->hide();
    this->ui->lineEdit_name->setText(name);
    this->setFixedSize(this->width(), 133);
    this->setWindowTitle(!name.isEmpty() ? "Подкаталог: " + name : "Новый подкаталог");

    QObject::connect(this->ui->pushButton_cancel, &QPushButton::clicked, this, &QDialog::reject);

    QSqlQuery q(SQL::db());
    q.exec("SELECT id, name FROM public.catalog;");
    //переписываем все каталоги в комбобокс и если индекс совпадает, то выбираем нужный вариант
    while (q.next())
    {
        const int id = q.value("id").toInt();
        const QString name = q.value("name").toString();
        this->ui->comboBox_cat->addItem(name, id);
        if (cat_id && id == cat_id)
        {
            this->ui->comboBox_cat->setCurrentIndex(this->ui->comboBox_cat->count() - 1);
        }
    }
    if (!cat_id) //если индекс не совпадает, выбираем дефолтный вариант
    {
        this->ui->comboBox_cat->setCurrentIndex(0);
    }
}

InputItem::InputItem(QWidget *parent, const QString &name, const int cat_id, const int sub_id) : //конструктор для категорий
    QDialog(parent), dialog_type(CATEGORY),
    ui(new Ui::InputItem)
{
    ui->setupUi(this);

    this->ui->lineEdit_name->setText(name);
    this->setFixedSize(this->width(), 180);
    this->setWindowTitle(!name.isEmpty() ? "Категория: " + name : "Новая категория");

    QObject::connect(this->ui->pushButton_cancel, &QPushButton::clicked, this, &QDialog::reject);

    QSqlQuery q(SQL::db());
    q.exec("SELECT id, name FROM public.catalog;");
    this->ui->comboBox_cat->addItem("Все", 0);
    //переписываем все каталоги в комбобокс и если индекс совпадает, то выбираем нужный вариант
    while (q.next())
    {
        const int id = q.value("id").toInt();
        const QString name = q.value("name").toString();
        this->ui->comboBox_cat->addItem(name, id);
        if (cat_id && id == cat_id)
        {
            this->ui->comboBox_cat->setCurrentIndex(this->ui->comboBox_cat->count() - 1);
        }
    }
    if (!cat_id) //если индекс не совпадает, выбираем дефолтный вариант
    {
        this->ui->comboBox_cat->setCurrentIndex(0);
    }

    for (int i = 0; i < this->ui->comboBox_sub->count(); ++i) //выбираем вариант для второго комбобокса
    {
        if (!sub_id)
        {
            this->ui->comboBox_sub->setCurrentIndex(0);
            break;
        }
        if (this->ui->comboBox_sub->itemData(i).toInt() == sub_id)
        {
            this->ui->comboBox_sub->setCurrentIndex(i);
            break;
        }
    }
}

InputItem::~InputItem() //деструктор
{
    delete ui;
}

void InputItem::setSubcat(QWidget *parent, QString &name, int &cat_id, bool *ok) //создание объекта как подкаталога
{
    auto dialog = new InputItem(parent, name, cat_id);
    if (ok != nullptr)
    {
        QObject::connect(dialog, &QDialog::finished, dialog, [&](int r){ *ok = r; });
    }
    QObject::connect(dialog, &InputItem::send_name, dialog, [&](const QString &n){ name = n; });
    QObject::connect(dialog, &InputItem::send_catalog, dialog, [&](const int id){ cat_id = id; });
    QObject::connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);
    dialog->exec();
}

void InputItem::setCategory(QWidget *parent, QString &name, int &sub_id, bool *ok) //создание объекта как категории
{
    auto dialog = new InputItem(parent, name, 0, sub_id);
    if (ok != nullptr)
    {
        QObject::connect(dialog, &QDialog::finished, dialog, [&](int r){ *ok = r; });
    }
    QObject::connect(dialog, &InputItem::send_name, dialog, [&](const QString &n){ name = n; });
    QObject::connect(dialog, &InputItem::send_subcat, dialog, [&](const int id){ sub_id = id; });
    QObject::connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);
    dialog->exec();
}

void InputItem::on_pushButton_ok_clicked() //завершаем работу с объектом и сохраняем изменения
{
    emit this->send_name(this->ui->lineEdit_name->text());
    switch (this->dialog_type)
    {
    case SUBCAT:
        emit this->send_catalog(this->ui->comboBox_cat->currentData().toInt());
        break;
    case CATEGORY:
        emit this->send_subcat(this->ui->comboBox_sub->currentData().toInt());
        break;
    }
    this->accept();
}


void InputItem::on_comboBox_cat_currentIndexChanged(int index) //если индекс комбобокса категорий изменен
{
    if (index < 0 || this->dialog_type == SUBCAT) return;

    this->ui->comboBox_sub->clear();
    QSqlQuery q(SQL::db());
    QString query = "SELECT id, name FROM public.subcatalog";
    const int id = this->ui->comboBox_cat->currentData().toInt();
    if (id)
    {
        query += " WHERE catalog_id = :cid";
    }
    query += ';';
    q.prepare(query);
    q.bindValue(":cid", id);
    q.exec();
    if (!q.size())
    {
        QMessageBox::warning(this, "Ошибка", "У данного каталога нет подкаталогов! Сначала добавьте хотя бы один или выберите другой каталог");
        this->ui->comboBox_cat->setCurrentIndex(0);
        return;
    }
    while (q.next())
    {
        const int id = q.value("id").toInt();
        const QString name = q.value("name").toString();
        this->ui->comboBox_sub->addItem(name, id);
    }
}

