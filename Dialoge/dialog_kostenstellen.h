#ifndef DIALOG_KOSTENSTELLEN_H
#define DIALOG_KOSTENSTELLEN_H

#include <QDialog>
#include "Klassen/kostenstellen.h"

namespace Ui {
class Dialog_Kostenstellen;
}

class Dialog_Kostenstellen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Kostenstellen(QWidget *parent = nullptr);
    ~Dialog_Kostenstellen();

private slots:
    void on_pushButton_abbrechen_clicked();

    void on_pushButton_ok_clicked();

    void on_tableWidget_kost_cellChanged(int row, int column);

private:
    Ui::Dialog_Kostenstellen *ui;
    kostenstellen KoSten;

protected:
 void showEvent(QShowEvent *e);
};

#endif // DIALOG_KOSTENSTELLEN_H
