#ifndef DIALOG_KOSTENSTELLEN_H
#define DIALOG_KOSTENSTELLEN_H

#include <QDialog>
#include <QMenu>

#include "Klassen/kostenstellen.h"
#include "Dialoge/dialog_kostenstelle.h"

namespace Ui {
class Dialog_Kostenstellen;
}

class Dialog_Kostenstellen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Kostenstellen(QWidget *parent = nullptr);
    ~Dialog_Kostenstellen();

private:
    void update_tablewidget();
    void kostenstellen_sortieren();

private slots:
    void resizeEvent(QResizeEvent *event);    
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
    void on_tableWidget_kost_customContextMenuRequested(const QPoint &pos);
    void on_pushButton_neu_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_entfernen_clicked();

signals:
    void signal_kost(kostenstellen);

private:
    Ui::Dialog_Kostenstellen *ui;
    kostenstellen KoSt;

protected:
 void showEvent(QShowEvent *e);
};

#endif // DIALOG_KOSTENSTELLEN_H
