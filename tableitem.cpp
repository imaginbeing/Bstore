#include "tableitem.h"

QPushButton *TableItem::button(const QString &text1, const int price, QWidget *parent) //создание кнопки для корзины
{
    auto pb = new QPushButton(parent);
    pb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    auto lay = new QVBoxLayout(pb);
    auto l = new QLabel(text1, pb);
    lay->addWidget(l);
    l = new QLabel(QString("%1 ₽ /шт").arg(price), pb);
    lay->addWidget(l);

    return pb;
}

QPushButton *TableItem::button(const QString &text, QWidget *parent, const bool bold) //содание кнопки для каталога и подкаталога
{
    auto pb = new QPushButton(parent);
    pb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    auto l = new QLabel(text, pb);
    l->setWordWrap(true);
    if (bold)
    {
        QFont f = l->font();
        f.setBold(true);
        f.setPointSize(f.pointSize() + 5);
        l->setFont(f);
    }

    auto lay = new QVBoxLayout(pb);
    lay->addWidget(l);

    return pb;
}

//создание кнопки для товара
QPushButton *TableItem::button(const QString &text, QWidget *parent, const double rate, const int comms, const int price)
{
    auto pb = new QPushButton(parent);
    pb->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    auto l = new QLabel(text, pb);
    l->setWordWrap(true);

    auto lay = new QGridLayout(pb);
    lay->addWidget(l, 0, 0, 1, 4);

    l = new QLabel(pb);
    l->setMinimumWidth(30);
    l->setPixmap(QPixmap::fromImage(QImage(":/star.png").scaled(l->size(), Qt::KeepAspectRatio)));
    lay->addWidget(l, 1, 0, 1, 1);

    l = new QLabel(pb);
    l->setNum(rate);
    lay->addWidget(l, 1, 1, 1, 1);

    l = new QLabel(pb);
    l->setMinimumWidth(30);
    l->setPixmap(QPixmap::fromImage(QImage(":/com.png").scaled(l->size(), Qt::KeepAspectRatio)));
    lay->addWidget(l, 1, 2, 1, 1);

    l = new QLabel(pb);
    l->setNum(int(comms));
    lay->addWidget(l, 1, 3, 1, 1);

    l = new QLabel(pb);
    l->setText(QString("%1 ₽ /шт").arg(price));
    lay->addWidget(l, 2, 0, 1, 4);

    return pb;
}

TableItem *TableItem::asCatalog(const int id, const QString &name) //компановка объектов в каталог
{
    auto layout = new QVBoxLayout(this);

    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    auto pb = this->button(name, this, true);
    pb->setToolTip(name);
    pb->setProperty("id", id);
    pb->setProperty("name", name);
    QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onCatalog);
    layout->addWidget(pb);

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, name FROM public.subcatalog WHERE catalog_id = :cid;");
    q.bindValue(":cid", id);
    q.exec();
    while (q.next())
    {
        const int subcat = q.value("id").toInt();
        const QString name = q.value("name").toString();
        auto pb = this->button(name, this, false);
        pb->setToolTip(name);
        pb->setProperty("id", subcat);
        pb->setProperty("name", name);
        QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onSubcat);
        layout->addWidget(pb);
    }

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    return this;
}

TableItem *TableItem::asSubcat(const int id, const QString &name) //компановка объектов в подкаталог
{
    auto layout = new QVBoxLayout(this);

    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    auto pb = this->button(name, this, true);
    pb->setToolTip(name);
    pb->setProperty("id", id);
    pb->setProperty("name", name);
    QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onSubcat);
    layout->addWidget(pb);

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, name FROM public.category WHERE subcatalog_id = :sid;");
    q.bindValue(":sid", id);
    q.exec();
    while (q.next())
    {
        const int category = q.value("id").toInt();
        const QString name = q.value("name").toString();
        auto pb = this->button(name, this, false);
        pb->setToolTip(name);
        pb->setProperty("id", category);
        pb->setProperty("name", name);
        QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onCategory);
        layout->addWidget(pb);
    }

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    return this;
}

TableItem *TableItem::asProduct(const int product, const QString &name, const int price) //компановка объектов в товар
{
    auto layout = new QVBoxLayout(this);

    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    QSqlQuery q(SQL::db());
    q.prepare("SELECT rate FROM public.review WHERE product_id = :pid;");
    q.bindValue(":pid", product);
    q.exec();
    int amount = 0;
    double average = 0;
    while (q.next())
    {
        average += q.value("rate").toInt();
        ++amount;
    }

    average /= (amount ? amount : 1);

    auto pb = this->button(name, this, average, amount, price);
    pb->setToolTip(name);
    pb->setProperty("id", product);
    QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onProduct);
    layout->addWidget(pb);

    pb = new QPushButton("В корзину", this);
    pb->setProperty("id", product);
    QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onCart);
    layout->addWidget(pb);

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    return this;
}

TableItem *TableItem::asReview(const int rate, const QString &review, const QString &username) //компановка компонентов в отзыв
{
    auto lay = new QVBoxLayout(this);

    lay->addWidget(new QLabel(QString("Пользователь %1").arg(username), this));
    lay->addWidget(new QLabel(QString("Оценка: %1/10").arg(rate), this));

    auto l = new QLabel(review, this);
    l->setWordWrap(true);
    l->setScaledContents(true);
    lay->addWidget(l);
    this->setFrameStyle(1);

    return this;
}

//компановка обектов в элемент корзины
TableItem *TableItem::asCartItem(const int product, const int cart, const QString &name, const int price, const int amount)
{
    auto layout = new QVBoxLayout(this);

    auto line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    auto pb = this->button(name, price, this);
    pb->setToolTip(name);
    pb->setProperty("product", product);
    pb->setProperty("cart", cart);
    QObject::connect(pb, &QPushButton::clicked, this, &TableItem::onCartProd);
    layout->addWidget(pb);

    auto sb = new QSpinBox(this);
    sb->setMinimum(0);
    sb->setMaximum(999);
    sb->setValue(amount);
    sb->setProperty("product", product);
    sb->setProperty("amount", amount);
    sb->setProperty("cart", cart);
    QObject::connect(sb, QOverload<int>::of(&QSpinBox::valueChanged), this, &TableItem::onCartSpin);
    layout->addWidget(sb);

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    return this;
}

void TableItem::onCatalog() //нажатие на каталог
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int id = obj->property("id").toInt();
    emit this->send_catalog(id);
    const QString name = obj->property("name").toString();
    emit this->send_name(name);
}

void TableItem::onSubcat() //нажатие на подкаталог
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int id = obj->property("id").toInt();
    emit this->send_subcat(id);
    const QString name = obj->property("name").toString();
    emit this->send_name(name);
}

void TableItem::onCategory() //нажатие на категорию
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int id = obj->property("id").toInt();
    emit this->send_category(id);
    const QString name = obj->property("name").toString();
    emit this->send_name(name);
}

void TableItem::onProduct() //нажатие не продукт
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int id = obj->property("id").toInt();
    emit this->send_product(id);
}

void TableItem::onCart() //нажатие на добавление в корзину
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int id = obj->property("id").toInt();
    emit this->send_cart(id);
}

void TableItem::onCartProd() //нажатие на продукт в корзине
{
    auto obj = qobject_cast<QObject *>(QObject::sender());
    const int cart = obj->property("cart").toInt();
    const int product = obj->property("product").toInt();
    emit this->send_cart(cart);
    emit this->send_product(product);
}

void TableItem::onCartSpin(int val) //нажатие на спинбокс продукта в корзине
{
    auto sb = qobject_cast<QSpinBox *>(QObject::sender());
    const int oldamount = sb->property("amount").toInt();
    const int product = sb->property("product").toInt();
    const int cart = sb->property("cart").toInt();
    if (val > oldamount)
    {
        const int inc = val - oldamount;
        QSqlQuery q(SQL::db());
        q.prepare("SELECT id FROM public.storage WHERE product_id = :pid AND amount >= :a;");
        q.bindValue(":pid", product);
        q.bindValue(":a", inc);
        q.exec();
        const bool exist = q.first();
        if (!exist)
        {
            QMessageBox::warning(this, "Ошибка", "Товара нет в наличии!");
            sb->setValue(oldamount);
            return;
        }
        else
        {
            const int storage = q.value("id").toInt();
            q.prepare("UPDATE public.storage SET amount = amount - :a WHERE id = :id;");
            q.bindValue(":a", inc);
            q.bindValue(":id", storage);
            q.exec();
            emit this->increase_cart(cart, inc);
        }
    }
    else if (val < oldamount)
    {
        QSqlQuery q(SQL::db());
        q.prepare("UPDATE public.storage SET amount = amount + :a WHERE product_id = :pid;");
        q.bindValue(":a", oldamount - val);
        q.bindValue(":pid", product);
        q.exec();
        emit this->decrease_cart(cart, oldamount - val);
    }
    sb->setProperty("amount", val);
}
