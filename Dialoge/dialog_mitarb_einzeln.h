#ifndef DIALOG_MITARB_EINZELN_H
#define DIALOG_MITARB_EINZELN_H

#include <QDialog>

#include "Klassen/mitarbeiter.h"

namespace Ui {
class Dialog_mitarb_einzeln;
}

class Dialog_mitarb_einzeln : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_mitarb_einzeln(QWidget *parent = nullptr);
    ~Dialog_mitarb_einzeln();
    void set_Mitarb (mitarbeiter *m);
    void set_Modus_neu();
    void set_Modus_edit();
    void set_akt_mitarb(QString nr);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_mitarb_einzeln *ui;
    mitarbeiter *Mitarb;
    int Modus;
};

#define MODUS_MITARB_NEU   1
#define MODUS_MITARB_EDIT  2
#endif // DIALOG_MITARB_EINZELN_H
