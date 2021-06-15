#ifndef DIALOG_TAGESZETTEL_H
#define DIALOG_TAGESZETTEL_H

#include <QDialog>
#include <QDate>

#include "Klassen/prgpfade.h"
#include "Klassen/arbeitszeiten.h"
#include "Klassen/mitarbeiter.h"
#include "Funktionen/dateien.h"
#include "Funktionen/text.h"

namespace Ui {
class Dialog_tageszettel;
}

class Dialog_tageszettel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_tageszettel(QWidget *parent = nullptr);
    ~Dialog_tageszettel();
    void set_Mitarb(mitarbeiter *m);
    void set_Arbzeit(arbeitszeiten *az);

private slots:
    void on_tableWidget_mitarb_cellClicked(int row, int column);

private:
    Ui::Dialog_tageszettel *ui;
    mitarbeiter *Mitarb;
    arbeitszeiten *Arbzeit;
    tabelle_qstring Tab_mitarb;

    void update_tab_mitarb();
};

#endif // DIALOG_TAGESZETTEL_H
