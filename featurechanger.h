#ifndef FEATURECHANGER_H
#define FEATURECHANGER_H

#include <QDialog>
#include <QMessageBox>

#include "sql.h"

namespace Ui {
class FeatureChanger;
}

class FeatureChanger : public QDialog
{
    Q_OBJECT
    int product;
    int prfeat;

public:
    explicit FeatureChanger(const int prod, const int feat = 0, QWidget *parent = nullptr);
    ~FeatureChanger();

    void setText(const QString &text);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_ok_clicked();

private:
    Ui::FeatureChanger *ui;
};

#endif // FEATURECHANGER_H
