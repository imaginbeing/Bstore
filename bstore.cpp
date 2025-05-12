#include "bstore.h"
#include "ui_bstore.h"

Bstore::Bstore(QWidget *parent) //конструктор
    : QMainWindow(parent)
    , ui(new Ui::Bstore)
{
    this->ui->setupUi(this);
    this->setWindowTitle("Bstore");
    this->ui->action_out->setVisible(false);
    this->ui->action_name->setVisible(false);
    this->ui->action_cart->setVisible(false);
    this->ui->pushButton_back->setEnabled(false);
    this->ui->widget_admin->hide();
    this->ui->widget_provider->hide();
    this->ui->pushButton_buy->hide();
    this->ui->tableWidget->setColumnCount(2);
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(this->ui->action_log, &QAction::triggered, this, &Bstore::callLogin);
    QObject::connect(this->ui->action_reg, &QAction::triggered, this, &Bstore::callReg);
    QObject::connect(this->ui->action_out, &QAction::triggered, this, &Bstore::callOut);
    QObject::connect(this->ui->action_name, &QAction::triggered, this, &Bstore::changeName);
    QObject::connect(this->ui->action_cart, &QAction::triggered, this, &Bstore::setTableAsCart);

    QObject::connect(this->ui->pushButton_feature, &QPushButton::clicked, std::bind(&Inputter::openFeature, this));
    QObject::connect(this->ui->pushButton_catalog, &QPushButton::clicked, std::bind(&Inputter::openCatalog, this));
    QObject::connect(this->ui->pushButton_subcat, &QPushButton::clicked, std::bind(&Inputter::openSubcat, this));
    QObject::connect(this->ui->pushButton_category, &QPushButton::clicked, std::bind(&Inputter::openCategory, this));

    QObject::connect(this->ui->pushButton_clients, &QPushButton::clicked, std::bind(&Storage::openUsers, this));
    QObject::connect(this->ui->pushButton_sellers, &QPushButton::clicked, std::bind(&Storage::openProviders, this));
    QObject::connect(this->ui->pushButton_admins, &QPushButton::clicked, std::bind(&Storage::openAdmins, this));

    this->setTableAsCatalog();
}

Bstore::~Bstore() //деструктор
{
    delete this->ui;
}

// Knauf 123321 Artem
// 123456 123456



void Bstore::callLogin() //вызов окна логина
{
    auto dialog = new Login(this);
    QObject::connect(dialog, &Login::send_id, this, &Bstore::set_id);
    QObject::connect(dialog, &Login::send_admin, this, &Bstore::set_admin);
    QObject::connect(dialog, &Login::send_provider, this, &Bstore::set_provider);
    QObject::connect(dialog, &Login::send_id, this, &Bstore::afterLogin);
    dialog->open();
}

void Bstore::callReg() //вызов окна регистрации
{
    auto dialog = new Reg(this);
    dialog->open();
}

void Bstore::callOut() //выход из аккаунта
{
    if (QMessageBox::question(this, "Выход", "Вы уверены, что хотите выйти?") == QMessageBox::No) return;

    this->id = 0;
    this->admin = false;
    this->provider = false;

    this->ui->menu->setTitle("Вход/Регистрация");

    this->ui->widget_admin->hide();
    this->ui->widget_provider->hide();

    this->ui->action_log->setVisible(true);
    this->ui->action_reg->setVisible(true);

    this->ui->action_out->setVisible(false);
    this->ui->action_name->setVisible(false);
    this->ui->action_cart->setVisible(false);

    this->setTableAsCatalog();
}

void Bstore::afterLogin() //завершение входа
{
    this->ui->menu->setTitle("Аккаунт");

    this->ui->action_log->setVisible(false);
    this->ui->action_reg->setVisible(false);

    this->ui->action_out->setVisible(true);
    this->ui->action_name->setVisible(true);
    this->ui->action_cart->setVisible(!this->admin && !this->provider);
}

void Bstore::set_admin(bool admin) //сеттер административных прав
{
    this->admin = admin;
    this->ui->widget_admin->setVisible(this->admin);
}

void Bstore::set_provider() //сеттер прав продавца
{
    this->provider = true;
    this->ui->widget_provider->setVisible(this->provider);
}

void Bstore::on_pushButton_prod_clicked() //открытие окна товаров продавца
{
    auto dialog = new ProviderProduct(this->id, this);
    dialog->open();
}

void Bstore::on_pushButton_sup_clicked() //открытие окна поставок продавца
{
    auto dialog = new Supply(this->id, this);
    dialog->open();
}

void Bstore::on_pushButton_supply_clicked() //открытие окна поставок администратора
{
    auto dialog = new Supply(this);
    dialog->open();
}

void Bstore::on_pushButton_str_clicked() //открытие окна склада продавца
{
    auto dialog = new Storage(this->id, this);
    dialog->open();
}

void Bstore::on_pushButton_storage_clicked() //открытие окна склада администратора
{
    auto dialog = new Storage(this);
    dialog->open();
}

void Bstore::setTableAsCatalog() //сеттер таблицы как каталога
{
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(2);
    this->ui->pushButton_back->setEnabled(false);
    this->ttype = CATALOG;
    this->ui->label_tname->setText("Каталоги");
    this->clearLayout(this->ui->verlay_category);
    this->ui->pushButton_buy->hide();

    QSqlQuery q(SQL::db());

    if (!SQL::db().open())
    {
        QMessageBox::information(this,"error","no database");
        ui->action_log->setEnabled(false);
        ui->action_reg->setEnabled(false);
    }
    q.exec("SELECT * FROM public.catalog;");

    this->ui->tableWidget->setRowCount(q.size() / 2 +(q.size() % 2));
    int amount = 0;
    while (q.next())
    {
        const int catalog = q.value("id").toInt();
        const QString name = q.value("name").toString();
        this->ui->tableWidget->setItem(amount / 2, amount % 2, new QTableWidgetItem());
        auto item = new TableItem(this->ui->tableWidget);
        QObject::connect(item, &TableItem::send_catalog, this, &Bstore::setTableAsSubcat);
        QObject::connect(item, &TableItem::send_subcat, this, &Bstore::setTableFromSubcat);
        QObject::connect(item, &TableItem::send_name, this->ui->label_tname, &QLabel::setText);
        this->ui->tableWidget->setCellWidget(amount / 2, amount % 2, item->asCatalog(catalog, name));
        ++amount;
    }
    this->ui->tableWidget->resizeRowsToContents();
}

void Bstore::setTableAsSubcat(const int catalog) //сеттер таблицы как подкаталога
{
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(2);
    this->ui->pushButton_back->setEnabled(true);
    this->ttype = SUBCATALOG;
    this->clearLayout(this->ui->verlay_category);
    this->ui->pushButton_buy->hide();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT name FROM public.catalog WHERE id = :id;");
    q.bindValue(":id", catalog);
    q.exec();
    if (q.first())
    {
        const QString name = q.value("name").toString();
        this->ui->label_tname->setText(name);
    }

    q.prepare("SELECT * FROM public.subcatalog WHERE catalog_id = :cid;");
    q.bindValue(":cid", catalog);
    q.exec();

    this->ui->tableWidget->setRowCount(q.size() / 2 + (q.size() % 2));
    int amount = 0;
    while (q.next())
    {
        const int subcat = q.value("id").toInt();
        const QString name = q.value("name").toString();
        this->ui->tableWidget->setItem(amount / 2, amount % 2, new QTableWidgetItem());
        auto item = new TableItem(this->ui->tableWidget);
        QObject::connect(item, &TableItem::send_subcat, this, &Bstore::setTableFromSubcat);
        QObject::connect(item, &TableItem::send_category, this, &Bstore::setTableFromCategory);
        QObject::connect(item, &TableItem::send_name, this->ui->label_tname, &QLabel::setText);
        this->ui->tableWidget->setCellWidget(amount / 2, amount % 2, item->asSubcat(subcat, name));
        ++amount;
    }
    this->ui->tableWidget->resizeRowsToContents();
    this->cat_id = catalog;
}

void Bstore::setTableAsCart() //сеттер таблицы как корзины
{
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(4);
    this->ui->pushButton_back->setEnabled(true);
    this->ttype = CART;
    this->clearLayout(this->ui->verlay_category);
    this->ui->pushButton_buy->show();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT * FROM public.cart WHERE client_id = :cid;");
    q.bindValue(":cid", this->id);
    q.exec();
    this->ui->tableWidget->setRowCount(q.size() / 4 + ((q.size() % 4) ? 1 : 0));
    int amount = 0;
    int sum = 0;
    while (q.next())
    {
        const int cart = q.value("id").toInt();
        const int product = q.value("product_id").toInt();
        const int amnt = q.value("amount").toInt();

        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT name, price FROM public.product WHERE id = :id;");
        q2.bindValue(":id", product);
        q2.exec();
        q2.first();
        const QString name = q2.value("name").toString();
        const int price = q2.value("price").toInt();
        sum += price * amnt;

        this->ui->tableWidget->setItem(amount / 4, amount % 4, new QTableWidgetItem());
        auto item = new TableItem(this->ui->tableWidget);
        QObject::connect(item, &TableItem::increase_cart, this, &Bstore::cartIncreaser);
        QObject::connect(item, &TableItem::decrease_cart, this, &Bstore::cartDecreaser);
        QObject::connect(item, &TableItem::send_product, this, &Bstore::callProduct);
        this->ui->tableWidget->setCellWidget(amount / 4, amount % 4, item->asCartItem(product, cart, name, price, amnt));
        ++amount;
    }
    this->ui->label_tname->setText(QString("Общая сумма: %1 ₽").arg(sum));
}

void Bstore::cartIncreaser(const int cart, const int size) //добавление в корзину
{
    QSqlQuery q(SQL::db());
    q.prepare("UPDATE public.cart SET amount = amount + :a WHERE id = :id;");
    q.bindValue(":a", size);
    q.bindValue(":id", cart);
    q.exec();
}

void Bstore::cartDecreaser(const int cart, const int size) //удаление из корзины
{
    QSqlQuery q(SQL::db());
    q.prepare("UPDATE public.cart SET amount = amount - :a WHERE id = :id;");
    q.bindValue(":a", size);
    q.bindValue(":id", cart);
    q.exec();

    q.prepare("SELECT amount FROM public.cart WHERE id = :id;");
    q.bindValue(":id", cart);
    q.exec();
    q.first();
    if (!q.value("amount").toInt())
    {
        q.prepare("DELETE FROM public.cart WHERE id = :id;");
        q.bindValue(":id", cart);
        q.exec();
        this->setTableAsCart();
    }
}

void Bstore::setTableFromSubcat(const int subcat) //сеттер таблицы из подкаталога
{
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(4);
    this->ui->pushButton_back->setEnabled(true);
    this->ttype = FROMSUB;
    this->createCategory(subcat);
    this->ui->pushButton_buy->hide();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT * FROM public.category WHERE subcatalog_id = :sid;");
    q.bindValue(":sid", subcat);
    q.exec();
    int amount = 0;
    while (q.next())
    {
        const int category = q.value("id").toInt();

        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT * FROM public.product WHERE category_id = :cid;");
        q2.bindValue(":cid", category);
        q2.exec();
        this->ui->tableWidget->setRowCount(this->ui->tableWidget->rowCount() + q2.size() / 4 + ((q2.size() % 4) ? 1 : 0));
        while (q2.next())
        {
            const int product = q2.value("id").toInt();
            const int price = q2.value("price").toInt();
            const QString name = q2.value("name").toString();
            this->ui->tableWidget->setItem(amount / 4, amount % 4, new QTableWidgetItem());
            auto item = new TableItem(this->ui->tableWidget);
            QObject::connect(item, &TableItem::send_product, this, &Bstore::callProduct);
            QObject::connect(item, &TableItem::send_cart, this, &Bstore::addToCart);
            this->ui->tableWidget->setCellWidget(amount / 4, amount % 4, item->asProduct(product, name, price));
            ++amount;
        }
    }
    this->ui->tableWidget->resizeRowsToContents();
}

void Bstore::setTableFromCategory(const int category) //сеттер таблицы из категорий
{
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setColumnCount(4);
    this->ui->pushButton_back->setEnabled(true);
    this->ttype = FROMCAT;
    this->ui->pushButton_buy->hide();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT subcatalog_id FROM public.category WHERE id = :id;");
    q.bindValue(":id", category);
    q.exec();
    q.first();
    const int subcat = q.value("subcatalog_id").toInt();
    this->createCategory(subcat, category);

    q.prepare("SELECT * FROM public.product WHERE category_id = :cid;");
    q.bindValue(":cid", category);
    q.exec();
    this->ui->tableWidget->setRowCount(q.size() / 4 + ((q.size() % 4) ? 1 : 0));
    int amount = 0;

    while (q.next())
    {
        const int product = q.value("id").toInt();
        const int price = q.value("price").toInt();
        const QString name = q.value("name").toString();
        this->ui->tableWidget->setItem(amount / 4, amount % 4, new QTableWidgetItem());
        auto item = new TableItem(this->ui->tableWidget);
        QObject::connect(item, &TableItem::send_product, this, &Bstore::callProduct);
        QObject::connect(item, &TableItem::send_cart, this, &Bstore::addToCart);
        this->ui->tableWidget->setCellWidget(amount / 4, amount % 4, item->asProduct(product, name, price));
        ++amount;
    }
    this->ui->tableWidget->resizeRowsToContents();
}

void Bstore::createCategory(const int subcat, const int category) //создание категорий
{
    if (!subcat) return;
    this->clearLayout(this->ui->verlay_category);

    QSqlQuery q(SQL::db());
    q.prepare("SELECT * FROM public.category WHERE subcatalog_id = :sid;");
    q.bindValue(":sid", subcat);
    q.exec();
    while (q.next())
    {
        const int tmpcategory = q.value("id").toInt();
        const QString name = q.value("name").toString();
        QPushButton *pb;
        this->ui->verlay_category->addWidget(pb = new QPushButton(name));
        pb->setAutoExclusive(true);
        pb->setProperty("id", tmpcategory);
        pb->setProperty("name", name);
        QObject::connect(pb, &QPushButton::clicked, this, &Bstore::categoryChanged);
        pb->setCheckable(true);
        if (category == tmpcategory) pb->setChecked(true);
    }
}

void Bstore::categoryChanged() //изменение категории
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int category = obj->property("id").toInt();
    const QString name = obj->property("name").toString();
    this->ui->label_tname->setText(name);
    this->setTableFromCategory(category);
}

void Bstore::clearLayout(QLayout *layout) //стереть категории
{
    if (layout == nullptr) return;

    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->widget())
        {
           delete item->widget();
        }
        delete item;
    }
}

void Bstore::on_pushButton_back_clicked() //кнопка хода назад
{
    switch (this->ttype)
    {
    case CATALOG: break;
    case SUBCATALOG:
        this->setTableAsCatalog();
        break;
    case FROMSUB:
        this->setTableAsSubcat(this->cat_id);
        break;
    case FROMCAT:
        this->setTableAsSubcat(this->cat_id);
        break;
    case CART:
        this->setTableAsCatalog();
        break;
    }
}

void Bstore::callProduct(const int product) //вызов окна продукта
{
    if (!this->id) Product::callAsAnon(product, this);
    else if (this->admin) Product::callAsAdmin(product, this->id, this);
    else if (this->provider) Product::callAsProv(product, this->id, this);
    else Product::callAsUser(product, this->id, this);
}

void Bstore::addToCart(const int product) //добавление в корзину
{
    if (!this->id)
    {
        QMessageBox::warning(this, "Ошибка", "Сначала войдите в свой аккаунт");
        return;
    }
    if (this->admin)
    {
        QMessageBox::warning(this, "Ошибка", "Администратор не имеет доступа к данному действию");
        return;
    }
    if (this->provider)
    {
        QMessageBox::warning(this, "Ошибка", "Продавец не имеет доступа к данному действию");
        return;
    }

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, amount FROM public.storage WHERE product_id = :pid AND amount >= 1;");
    q.bindValue(":pid", product);
    q.exec();
    const bool exist = q.first();
    if (!exist)
    {
        QMessageBox::warning(this, "Ошибка", "Недостаточно товара на складе!");
        return;
    }
    const int storage = q.value("id").toInt();
    q.prepare("UPDATE public.storage SET amount = amount - 1 WHERE id = :id;");
    q.bindValue(":id", storage);
    q.exec();

    q.prepare("SELECT id FROM public.cart WHERE product_id = :pid AND client_id = :cid;");
    q.bindValue(":pid", product);
    q.bindValue(":cid", this->id);
    q.exec();
    if (q.first())
    {
        const int cart = q.value("id").toInt();
        q.prepare("UPDATE public.cart SET amount = amount + 1 WHERE id = :id;");
        q.bindValue(":id", cart);
        q.exec();
    }
    else
    {
        q.prepare("INSERT INTO public.cart (id, client_id, product_id, amount) VALUES (DEFAULT, :cid, :pid, 1);");
        q.bindValue(":cid", this->id);
        q.bindValue(":pid", product);
        q.exec();
    }
    QMessageBox::information(this, "Информация", "Добавлено!");
}

void Bstore::changeName() //изменение имени
{
    QSqlQuery q(SQL::db());
    q.prepare(QString("SELECT name FROM public.%1 WHERE id = :id;").arg(this->provider ? "provider" : "clients"));
    q.bindValue(":id", this->id);
    q.exec();
    q.first();
    QString name = q.value("name").toString();
    while (true)
    {
        bool fl;
        const QString newName = QInputDialog::getText(this, "Изменить имя", "Введите новое имя:",
                                                      QLineEdit::Normal, name, &fl, Qt::MSWindowsFixedSizeDialogHint);
        if (!fl) return;
        if (newName == name) return;
        if (newName.trimmed().isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Имя не должно быть пустым");
            continue;
        }
        if (newName.size() > 128)
        {
            QMessageBox::warning(this, "Ошибка", "Длина имени не должна быть больше 128 символов!");
            continue;
        }
        name = newName;
        break;
    }


    q.prepare(QString("UPDATE public.%1 SET name = :n WHERE id = :id;").arg(this->provider ? "provider" : "clients"));
    q.bindValue(":n", name);
    q.bindValue(":id", this->id);
    q.exec();
    QMessageBox::information(this, "Информация", "Имя успешно изменено!");
}

void Bstore::on_pushButton_buy_clicked() //покупка корзины
{
    QSqlQuery q(SQL::db());
    q.prepare("SELECT id FROM public.cart WHERE client_id = :cid;");
    q.bindValue(":cid", this->id);
    q.exec();
    q.first();
    if ( q.value("id").isNull() ) // проверка наполнения
    {

        QMessageBox::information(this, "Корзина", "Корзна пуста");
    }
    else
    {
    q.clear();
    q.prepare("DELETE FROM public.cart WHERE client_id = :cid;");
    q.bindValue(":cid", this->id);
    q.exec();
    QMessageBox::information(this, "Покупка", "Спасибо за покупку!");
    this->setTableAsCatalog();
    }
}

