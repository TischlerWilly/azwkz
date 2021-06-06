#ifndef DIALOG_KOSTENSTELLE_H
#define DIALOG_KOSTENSTELLE_H

#include <QDialog>

#include "Klassen/kostenstellen.h"
#include "Funktionen/umwandeln.h"

namespace Ui {
class Dialog_kostenstelle;
}

class Dialog_kostenstelle : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_kostenstelle(QWidget *parent = nullptr);
    ~Dialog_kostenstelle();
    void set_KoSt(kostenstellen *k);
    void set_Modus_neu();
    void set_Modus_edit();
    void set_akt_kost(QString nr);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_kostenstelle *ui;
    kostenstellen *KoSt;
    int Modus;
};

#define MODUS_KST_NEU   1
#define MODUS_KST_EDIT  2
#endif // DIALOG_KOSTENSTELLE_H
