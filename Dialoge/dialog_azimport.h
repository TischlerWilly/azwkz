#ifndef DIALOG_AZIMPORT_H
#define DIALOG_AZIMPORT_H

#include <QDialog>
#include <QDate>

#include "Klassen/prgpfade.h"
#include "Klassen/arbeitszeiten.h"
#include "Klassen/mitarbeiter.h"
#include "Funktionen/dateien.h"
#include "Funktionen/text.h"

namespace Ui {
class Dialog_azimport;
}

class Dialog_azimport : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_azimport(QWidget *parent = nullptr);
    ~Dialog_azimport();
    void set_Mitarb(mitarbeiter *m);
    void set_Arbzeit(arbeitszeiten *az);

private slots:
    void on_pushButton_import_clicked();
    void update_tabelle();

private:
    Ui::Dialog_azimport *ui;
    mitarbeiter *Mitarb;
    arbeitszeiten *Arbzeit;
};

#endif // DIALOG_AZIMPORT_H
