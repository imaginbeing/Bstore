#include "featurechanger.h"
#include "ui_featurechanger.h"

FeatureChanger::FeatureChanger(const int prod, const int feat, QWidget *parent) : //конструктор
    QDialog(parent), product(prod), prfeat(feat),
    ui(new Ui::FeatureChanger)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Характеристика");

    QObject::connect(this->ui->pushButton_cancel, &QPushButton::clicked, this, &QDialog::reject);

    if (this->prfeat)
    {
        this->ui->label->hide();
        this->ui->comboBox->hide();
    }
    else
    {
        QSqlQuery q(SQL::db());
        q.exec("SELECT id, name FROM public.feature;");
        while (q.next())
        {
            const int id = q.value("id").toInt();
            const QString name = q.value("name").toString();
            this->ui->comboBox->addItem(name, id);
        }
    }
}

FeatureChanger::~FeatureChanger() //деструктор
{
    delete ui;
}

void FeatureChanger::setText(const QString &text) //сеттер текста
{
    this->ui->lineEdit->setText(text);
}

void FeatureChanger::on_comboBox_currentIndexChanged(int index) //изменение индекса комбобокса
{
    if (index < 0) return;

    QSqlQuery q(SQL::db());
    q.prepare("SELECT description FROM public.product_feature WHERE product_id = :pid AND feature_id = :fid;");
    const int fid = this->ui->comboBox->currentData().toInt();
    q.bindValue(":pid", this->product);
    q.bindValue(":fid", fid);
    q.exec();
    if (q.first())
    {
        const QString desc = q.value("description").toString();
        this->ui->lineEdit->setText(desc);
    }
    else
    {
        this->ui->lineEdit->clear();
    }
}


void FeatureChanger::on_pushButton_ok_clicked() //нажатие кнопки принять изменения
{
    if (!this->prfeat && this->ui->comboBox->currentIndex() < 0)
    {
        QMessageBox::warning(this, "Ошибка", "Характеристика не выбрана!");
        return;
    }

    if (this->ui->lineEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Описание не должно быть пустым!");
        return;
    }

    if (this->prfeat)
    {
        QSqlQuery q(SQL::db());
        q.prepare("SELECT description FROM public.product_feature WHERE id = :id;");
        q.bindValue(":id", this->prfeat);
        q.exec();

        q.first();
        const QString desc = q.value("description").toString();
        if (desc == this->ui->lineEdit->text())
        {
            this->reject();
            return;
        }

        if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите обновить данную характеристику?") == QMessageBox::No) return;

        q.prepare("UPDATE public.product_feature SET description = :d WHERE id = :id;");
        q.bindValue(":d", this->ui->lineEdit->text());
        q.bindValue(":id", this->prfeat);
        q.exec();

        QMessageBox::information(this, "Информация", "Характеристика успешно обновлена!");
    }
    else
    {
        QSqlQuery q(SQL::db());
        q.prepare("SELECT id, description FROM public.product_feature WHERE product_id = :pid AND feature_id = :fid;");
        q.bindValue(":pid", this->product);
        q.bindValue(":fid", this->ui->comboBox->currentData());
        q.exec();

        const bool exist = q.first();
        if (exist)
        {
            const QString desc = q.value("description").toString();
            if (desc == this->ui->lineEdit->text())
            {
                this->reject();
                return;
            }

            if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите обновить данную характеристику?") == QMessageBox::No) return;

            const int id = q.value("id").toInt();
            q.prepare("UPDATE public.product_feature SET description = :d WHERE id = :id;");
            q.bindValue(":d", this->ui->lineEdit->text());
            q.bindValue(":id", id);
            q.exec();

            QMessageBox::information(this, "Информация", "Характеристика успешно обновлена!");
        }
        else
        {
            if (QMessageBox::question(this, "Предупреждение", "Вы уверены, что хотите добавить новую характеристику?") == QMessageBox::No) return;

            q.prepare("INSERT INTO public.product_feature (id, product_id, feature_id, description) "
                      "VALUES (DEFAULT, :pid, :fid, :d);");
            q.bindValue(":pid", this->product);
            q.bindValue(":fid", this->ui->comboBox->currentData());
            q.bindValue(":d", this->ui->lineEdit->text());
            q.exec();

            QMessageBox::information(this, "Информация", "Характеристика успешно добавлена!");
        }
    }
    this->accept();
}

