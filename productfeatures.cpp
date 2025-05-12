#include "productfeatures.h"
#include "ui_productfeatures.h"

ProductFeatures::ProductFeatures(const int id, QWidget *parent) : //конструктор
    QDialog(parent), id(id),
    ui(new Ui::ProductFeatures)
{
    ui->setupUi(this);
    this->setWindowTitle("Характеристики");
    this->setFixedSize(this->size());

    QObject::connect(this, &QDialog::finished, this, &QObject::deleteLater);
    this->update_list();
}

ProductFeatures::~ProductFeatures() //деструктор
{
    delete ui;
}

void ProductFeatures::update_list() //обновление листа характеристик
{
    this->ui->listWidget->clear();

    QSqlQuery q(SQL::db());
    q.prepare("SELECT id, feature_id, description FROM public.product_feature WHERE product_id = :pid;");
    q.bindValue(":pid", this->id);
    q.exec();
    while (q.next())
    {
        QSqlQuery q2(SQL::db());
        q2.prepare("SELECT name FROM public.feature WHERE id = :id;");
        const int fid = q.value("feature_id").toInt();
        q2.bindValue(":id", fid);
        q2.exec();
        q2.first();
        const QString name = q2.value("name").toString();
        const QString desc = q.value("description").toString();

        auto item = new QListWidgetItem(name, this->ui->listWidget);
        const int id = q.value("id").toInt();
        item->setData(Qt::UserRole, id);
        item->setToolTip(desc);
    }
}

void ProductFeatures::on_pushButton_add_clicked() //добавление характеристики
{
    auto dialog = new FeatureChanger(this->id, 0, this);
    QObject::connect(dialog, &QDialog::accepted, this, &ProductFeatures::update_list);
    QObject::connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);
    dialog->open();
}


void ProductFeatures::on_pushButton_del_clicked() //удаление характеристики
{
    if (this->ui->listWidget->currentRow() < 0) return;
    if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите удалить данную характеристику?") == QMessageBox::No) return;

    QSqlQuery q(SQL::db());
    q.prepare("DELETE FROM public.product_feature WHERE id = :id;");
    const int id = this->ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
    q.bindValue(":id", id);
    q.exec();

    QMessageBox::information(this, "Информация", "Характеристика успешно удалена!");
    this->update_list();
}

void ProductFeatures::on_listWidget_itemDoubleClicked(QListWidgetItem *item) //изменение характеристики, путем двойного нажатия на нее
{
    auto dialog = new FeatureChanger(this->id, item->data(Qt::UserRole).toInt(), this);
    dialog->setText(item->toolTip());
    QObject::connect(dialog, &QDialog::accepted, this, &ProductFeatures::update_list);
    QObject::connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);
    dialog->open();
}

