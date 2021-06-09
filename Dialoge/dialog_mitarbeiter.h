#ifndef DIALOG_MITARBEITER_H
#define DIALOG_MITARBEITER_H

#include <QDialog>
#include <QMenu>

#include "Klassen/mitarbeiter.h"


namespace Ui {
class Dialog_Mitarbeiter;
}

class Dialog_Mitarbeiter : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Mitarbeiter(QWidget *parent = nullptr);
    ~Dialog_Mitarbeiter();

private:
    void update_tablewidget();
    void mitarb_sortieren();

private slots:
    void resizeEvent(QResizeEvent *event);
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_neu_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_entfernen_clicked();
    void on_tableWidget_kost_customContextMenuRequested(const QPoint &pos);

signals:
    void signal_mitarb(mitarbeiter);

private:
    Ui::Dialog_Mitarbeiter *ui;
    mitarbeiter Mitarb;

protected:
 void showEvent(QShowEvent *e);

};

#endif // DIALOG_MITARBEITER_H
