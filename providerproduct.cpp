#include "providerproduct.h"
#include "ui_providerproduct.h"

ProviderProduct::ProviderProduct(const int id, QWidget *parent) : //конструктор
    QDialog(parent), provider(id),
    ui(new Ui::ProviderProduct)
{
    this->ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Товары");

    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);

    this->reset_list();
}

ProviderProduct::~ProviderProduct() //деструктор
{
    delete ui;
}

void ProviderProduct::reset_list() //обновить лист
{
    this->ui->listWidget->clear();
    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, name FROM public.product WHERE provider_id = :pid;");
    q.bindValue(":pid", this->provider);
    q.exec();
    while (q.next())
    {
        const int id = q.value("id").toInt();
        const QString name = q.value("name").toString();
        auto item = new QListWidgetItem(name, this->ui->listWidget);
        item->setData(Qt::UserRole, id);
    }
}

void ProviderProduct::on_pushButton_add_clicked() //добавление продукта
{
    auto dialog = new ProductChanger(this->provider, 0, this);
    QObject::connect(dialog, &QDialog::accepted, this, &ProviderProduct::reset_list);
    QObject::connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);
    dialog->open();
}

void ProviderProduct::on_pushButton_del_clicked() //удалние продукта
{
    if (this->ui->listWidget->currentRow() < 0) return;
    if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите удалить данный товар?") == QMessageBox::No) return;

    QSqlQuery q(SQL::db());
    q.prepare("DELETE FROM public.product WHERE id = :id;");
    const int id = this->ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
    q.bindValue(":id", id);
    q.exec();

    QMessageBox::information(this, "Информация", "Товар успешно удален!");
    this->reset_list();
}

void ProviderProduct::on_pushButton_sup_clicked() //отправка поставки
{
    if (this->ui->listWidget->currentRow() < 0) return;

    bool fl;
    int amount = QInputDialog::getInt(this, "Поставка", "Введите размер поставки, в шт.",
                                      3, 1, 999, 1, &fl, Qt::MSWindowsFixedSizeDialogHint);
    if (!fl) return;

    QSqlQuery q(SQL::db());
    q.prepare("INSERT INTO public.supply (id, product_id, amount, approved, request_date, approve_date) "
              "VALUES (DEFAULT, :pid, :a, DEFAULT, CURRENT_DATE, NULL);");
    q.bindValue(":pid", this->ui->listWidget->currentItem()->data(Qt::UserRole));
    q.bindValue(":a", amount);
    q.exec();

    QMessageBox::information(this, "Информация", "Поставка отправлена на рассмотрение. Проследить за состоянием поставки можно посмотреть в разделе поставок.");
}

void ProviderProduct::on_listWidget_itemDoubleClicked(QListWidgetItem *item) //изменение продукта
{
    auto dialog = new ProductChanger(this->provider, item->data(Qt::UserRole).toInt(), this);
    QObject::connect(dialog, &QDialog::finished, this, &ProviderProduct::reset_list);
    QObject::connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);
    dialog->open();
}

