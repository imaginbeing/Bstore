#include "product.h"
#include "ui_product.h"

Product::Product(const int id, const int user, const UType ut, QWidget *parent) : //конструктор
    QDialog(parent), utype(ut), id(id), user(user),
    ui(new Ui::Product)
{
    ui->setupUi(this);
    this->setFixedWidth(this->width());
    this->ui->widget_review->hide();
    if (this->utype != USER) this->ui->pushButton_leftRev->hide();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT * FROM public.product WHERE id = :id;");
    q.bindValue(":id", this->id);
    q.exec();
    q.first();

    const QString name = q.value("name").toString();
    this->ui->label_name->setText(QString("Название: %1").arg(name));
    this->ui->label_name->setToolTip(name);
    this->setWindowTitle(name);

    const int price = q.value("price").toInt();
    this->ui->label_price->setText(QString("Цена: %1 ₽ / шт").arg(price));
    this->ui->label_price->setToolTip(QString("%1 ₽ / шт").arg(price));

    const QString desc = q.value("description").toString();
    this->ui->textEdit_desc->setText(desc);

    const QString purpose = q.value("purpose").toString();
    auto lay = new QGridLayout(this->ui->scrollAreaWidgetContents);
    auto l = new QLabel("Назначение", this->ui->scrollAreaWidgetContents);
    auto f = l->font();
    f.setBold(true);
    l->setFont(f);
    lay->addWidget(l, 0, 0);
    lay->addWidget(new QLabel(purpose, this->ui->scrollAreaWidgetContents), 0, 1);

    q.prepare("SELECT feature_id, description FROM public.product_feature WHERE product_id = :pid;");
    q.bindValue(":pid", this->id);
    q.exec();
    int row = 1;
    while (q.next())
    {
        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT name FROM public.feature WHERE id = :id;");
        const int feature = q.value("feature_id").toInt();
        q2.bindValue(":id", feature);
        q2.exec();
        q2.first();

        const QString fname = q2.value("name").toString();
        auto l = new QLabel(fname, this->ui->scrollAreaWidgetContents);
        auto f = l->font();
        f.setBold(true);
        l->setFont(f);
        lay->addWidget(l, row, 0);

        const QString fdesc = q.value("description").toString();
        lay->addWidget(new QLabel(fdesc, this->ui->scrollAreaWidgetContents), row, 1);
        ++row;
    }

    lay->addItem(new QSpacerItem(100, 100, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 2);

    this->setReviews();

    q.prepare("SELECT amount FROM public.storage WHERE product_id = :pid;");
    q.bindValue(":pid", this->id);
    q.exec();
    const bool exist = q.first();
    if (exist)
    {
        const int amount = q.value("amount").toInt();
        if (amount)
        {
            this->ui->label_supply->setText("Наличие: в наличии");
            this->ui->label_supply->setToolTip("В наличии");
        }
        else
        {
            this->ui->label_supply->setText("Наличие: нет в наличии");
            this->ui->label_supply->setToolTip("Нет в наличии");
        }
    }
    else
    {
        this->ui->label_supply->setText("Наличие: нет в наличии");
        this->ui->label_supply->setToolTip("Нет в наличии");
    }
    bool hideHistory = true;
    if (this->utype == USER)
    {
        q.prepare("SELECT product_id FROM public.history WHERE client_id = :cid;");
        q.bindValue(":cid", this->user);
        q.exec();
        if (q.size() > 0)
        {
            this->ui->tableWidget_history->setRowCount(1);
            this->ui->tableWidget_history->setColumnCount(4);
            this->ui->tableWidget_history->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            int col = 0;
            while (q.next())
            {
                const int product = q.value("product_id").toInt();
                if (product == this->id)
                {
                    if (q.size() == 1) break;
                    continue;
                }
                QSqlQuery q2(SQL::db());
                q2.prepare("SELECT name, price FROM public.product WHERE id = :id;");
                q2.bindValue(":id", product);
                q2.exec();
                q2.first();
                const QString pname = q2.value("name").toString();
                const int price = q2.value("price").toInt();

                this->ui->tableWidget_history->setItem(0, col, new QTableWidgetItem());
                auto itemW = new TableItem(this);
                QObject::connect(itemW, &TableItem::send_product, this, &Product::callAgain);
                QObject::connect(itemW, &TableItem::send_cart, this, QOverload<>::of(&Product::addToCart));
                this->ui->tableWidget_history->setCellWidget(0, col, itemW->asProduct(product, pname, price));
                ++col;
            }
            hideHistory = !col;

        }
        this->ui->tableWidget_history->resizeRowsToContents();

        q.prepare("SELECT id, product_id FROM public.history WHERE client_id = :cid;");
        q.bindValue(":cid", this->user);
        q.exec();
        bool newHistory = true;
        QMap<int, int> history_product;
        while (q.next())
        {
            const int historyid = q.value("id").toInt();
            const int productid = q.value("product_id").toInt();
            if (productid == this->id) newHistory = false;
            history_product.insert(historyid, productid);
        }
        if (newHistory)
        {
            if (q.size() < 5)
            {
                q.prepare("INSERT INTO public.history (id, client_id, product_id) VALUES (DEFAULT, :cid, :pid);");
                q.bindValue(":cid", this->user);
                q.bindValue(":pid", this->id);
                q.exec();
            }
            else
            {
                int nextProduct = this->id;
                QMapIterator<int, int> item(history_product);
                while (item.hasNext())
                {
                    item.next();
                    q.prepare("UPDATE public.history SET product_id = :pid WHERE id = :id;");
                    q.bindValue(":pid", nextProduct);
                    q.bindValue(":id", item.key());
                    q.exec();
                    nextProduct = item.value();
                }
            }
        }
    }
    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);

    if (hideHistory)
    {
        this->ui->label_watched->hide();
        this->ui->tableWidget_history->hide();
        this->setFixedHeight(410);
    }
}

Product::~Product() //деструктор
{
    delete ui;
}

void Product::callAsAnon(const int id, QWidget *parent) //открытие окна анонимно
{
    auto dialog = new Product(id, 0, ANON, parent);
    dialog->open();
}

void Product::callAsUser(const int id, const int user, QWidget *parent) //открытие окна как клиент
{
    auto dialog = new Product(id, user, USER, parent);
    dialog->open();
}

void Product::callAsAdmin(const int id, const int user, QWidget *parent) //открытие окна как админ
{
    auto dialog = new Product(id, user, ADMIN, parent);
    dialog->open();
}

void Product::callAsProv(const int id, const int user, QWidget *parent) //открытие окна как продавец
{
    auto dialog = new Product(id, user, PROVIDER, parent);
    dialog->open();
}

void Product::callAgain(const int product) //вызов следующего окна
{
    auto dialog = new Product(product, this->user, USER, this->parentWidget());
    dialog->open();
    this->close();
}

void Product::on_pushButton_review_clicked() //добавление отзыва
{
    if (this->utype != this->USER)
    {
        QMessageBox::warning(this, "Ошибка", "Отзыв могут оставлять только клиенты!");
        return;
    }
    if (this->ui->textEdit_review->toHtml().size() > 4096)
    {
        QMessageBox::warning(this, "Ошибка", "Отзыв слишком большой!");
        return;
    }
    QSqlQuery q(SQL::db());
    q.prepare("SELECT id FROM public.review WHERE client_id = :cid;");
    q.bindValue(":cid", this->user);
    q.exec();
    const bool exist = q.first();

    if (exist)
    {
        if (QMessageBox::question(this, "Предупреждение", "Вы уже оставляли свой отзыв, хотите ли вы его изменить?") == QMessageBox::No) return;
        const int reviewid = q.value("id").toInt();
        q.prepare("UPDATE public.review SET rate = :ra, review = :re WHERE id = :id;");
        q.bindValue(":ra", this->ui->spinBox_rate->value());
        q.bindValue(":re", this->ui->textEdit_review->toHtml());
        q.bindValue(":id", reviewid);
        q.exec();
    }
    else
    {
        q.prepare("INSERT INTO public.review (id, client_id, product_id, rate, review) "
                  "VALUES (DEFAULT, :cid, :pid, :ra, :re);");
        q.bindValue(":cid", this->user);
        q.bindValue(":pid", this->id);
        q.bindValue(":ra", this->ui->spinBox_rate->value());
        q.bindValue(":re", this->ui->textEdit_review->toHtml());
        q.exec();
    }
    QMessageBox::information(this, "Информация", "Отзыв оставлен!");

    this->ui->textEdit_review->clear();
    this->ui->spinBox_rate->setValue(10);
    this->ui->pushButton_leftRev->click();
    this->setReviews();
}

void Product::on_pushButton_leftRev_clicked(bool checked) //скрытие формы отзыва
{
    this->ui->widget_review->setVisible(checked);
}

void Product::setReviews() //сеттер отзывов
{
    this->ui->tableWidget_review->clear();
    QSqlQuery q(SQL::db());
    q.prepare("SELECT client_id, rate, review FROM public.review WHERE product_id = :pid;");
    q.bindValue(":pid", this->id);
    q.exec();
    this->ui->tabWidget->setTabText(2, QString("Отзывы (%1)").arg(q.size()));
    int amount = q.size();
    double average = 0;
    this->ui->tableWidget_review->setRowCount(amount);
    this->ui->tableWidget_review->setColumnCount(1);
    this->ui->tableWidget_review->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int row = 0;
    while (q.next())
    {
        const int rate = q.value("rate").toInt();
        average += rate;

        this->ui->tableWidget_review->setItem(row, 0, new QTableWidgetItem());
        auto itemW = new TableItem(this->ui->tableWidget_review);
        const QString review = q.value("review").toString();

        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT name FROM public.clients WHERE id = :id;");
        const int userid = q.value("client_id").toInt();
        q2.bindValue(":id", userid);
        q2.exec();
        q2.first();
        const QString username = q2.value("name").toString();
        this->ui->tableWidget_review->setCellWidget(row, 0, itemW->asReview(rate, review, username));
        ++row;
    }
    this->ui->tableWidget_review->resizeRowsToContents();

    average /= amount ? amount : 1;
    this->ui->label_rate->setText(QString("Оценка: %1/10").arg(average));
    this->ui->label_price->setToolTip(QString("Оценка: %1/10").arg(average));
}

void Product::addToCart(const int amount) //добавление в корзину
{
    if (this->utype != USER)
    {
        QMessageBox::warning(this, "Ошибка", "Покупать товары могут только авторизованные клиенты!");
        return;
    }

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, amount FROM public.storage WHERE product_id = :pid AND amount >= :a;");
    q.bindValue(":pid", this->id);
    q.bindValue(":a", amount);
    q.exec();
    const bool exist = q.first();
    if (!exist)
    {
        QMessageBox::warning(this, "Ошибка", "Недостаточно товара на складе!");
        return;
    }
    const int storage = q.value("id").toInt();
    q.prepare("UPDATE public.storage SET amount = amount - :a WHERE id = :id;");
    q.bindValue(":a", amount);
    q.bindValue(":id", storage);
    q.exec();

    q.prepare("SELECT id FROM public.cart WHERE product_id = :pid AND client_id = :cid;");
    q.bindValue(":pid", this->id);
    q.bindValue(":cid", this->user);
    q.exec();
    if (q.first())
    {
        const int cart = q.value("id").toInt();
        q.prepare("UPDATE public.cart SET amount = amount + :a WHERE id = :id;");
        q.bindValue(":a", amount);
        q.bindValue(":id", cart);
        q.exec();
    }
    else
    {
        q.prepare("INSERT INTO public.cart (id, client_id, product_id, amount) VALUES (DEFAULT, :cid, :pid, 1);");
        q.bindValue(":cid", this->user);
        q.bindValue(":pid", this->id);
        q.exec();
    }
    QMessageBox::information(this, "Информация", "Добавлено!");
}

void Product::on_pushButton_buy_clicked() //добавление в корзину
{
    this->addToCart(this->ui->spinBox_amount->value());
}

void Product::addToCart() { this->addToCart(1); } //добавление в корзину
