#ifndef DIALOG_KOSTENSTELLEN_H
#define DIALOG_KOSTENSTELLEN_H

#include <QDialog>
#include <QMenu>
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
    void resizeEvent(QResizeEvent *event);
    void zeile_anhaengen();
    void kostenstellen_sortieren();
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
    void on_tableWidget_kost_cellChanged(int row, int column);
    void on_tableWidget_kost_itemSelectionChanged();
    void on_tableWidget_kost_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Dialog_Kostenstellen *ui;
    kostenstellen KoSten;
    bool tabellenupdate;
    QString daten_vor_aenderung;

protected:
 void showEvent(QShowEvent *e);
};

#endif // DIALOG_KOSTENSTELLEN_H
