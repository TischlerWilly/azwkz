#include "dialog_mitarb_einzeln.h"
#include "ui_dialog_mitarb_einzeln.h"

Dialog_mitarb_einzeln::Dialog_mitarb_einzeln(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_mitarb_einzeln)
{
    ui->setupUi(this);
    Mitarb = NULL;
    Modus = 0;
}
Dialog_mitarb_einzeln::~Dialog_mitarb_einzeln()
{
    delete ui;
}
void Dialog_mitarb_einzeln::set_Mitarb(mitarbeiter *m)
{
    Mitarb = m;
}
void Dialog_mitarb_einzeln::set_Modus_neu()
{
    Modus = MODUS_MITARB_NEU;
    ui->lineEdit_nr->setEnabled(true);
}
void Dialog_mitarb_einzeln::set_Modus_edit()
{
    Modus = MODUS_MITARB_EDIT;
    ui->lineEdit_nr->setDisabled(true);
}
void Dialog_mitarb_einzeln::set_akt_mitarb(QString nr)
{
    if(Mitarb == NULL)
    {
        QString msg;
        msg = "Zuvor muss Zeiger auf Kostenstellen übergeben werden.\n";
        msg += "Bitte wenden Sie sich an Ihren Administrator.";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Fehler Dialog_kostenstelle");
        mb.exec();
    }else
    {
        liste_QString lqs = Mitarb->zeile_nr(nr);
        ui->lineEdit_nr->setText(lqs.wert(INDEX_MITARB_NUMMER));
        ui->lineEdit_vona->setText(lqs.wert(INDEX_MITARB_VORNAME));
        ui->lineEdit_nana->setText(lqs.wert(INDEX_MITARB_NACHNAME));
        ui->lineEdit_idscan->setText(lqs.wert(INDEX_MITARB_IDSCANNER));
    }
}
void Dialog_mitarb_einzeln::on_pushButton_ok_clicked()
{
    QString nr = ui->lineEdit_nr->text();
    QString vona = ui->lineEdit_vona->text();
    QString nana = ui->lineEdit_nana->text();
    QString idscan = ui->lineEdit_idscan->text();

    if(nr.isEmpty())
    {
        QMessageBox mb;
        mb.setText("Bitte geben Sie noch eine Personalnummer ein.");
        mb.exec();
    }else if(vona.isEmpty())
    {
        QMessageBox mb;
        mb.setText("Bitte geben Sie noch einen Vornamen ein.");
        mb.exec();
    }else if(nana.isEmpty())
    {
        QMessageBox mb;
        mb.setText("Bitte geben Sie noch einen Nachnamen ein.");
        mb.exec();
    }else if(Mitarb->set_idscanner(nr, idscan) == 2)
    {
        QMessageBox mb;
        mb.setText("Scanner-ID ist bereits vergeben.");
        mb.exec();
    }else
    {
        liste_QString lqs;
        lqs.anhaengen(nr);
        lqs.anhaengen(vona);
        lqs.anhaengen(nana);
        lqs.anhaengen(idscan);

        if(Modus == MODUS_MITARB_NEU)
        {
            if(Mitarb->add(lqs))//Wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Einen Mitarbeiter mit dieser Personalnummer gibt es bereits.\nBitten wählen Sie eine andere Nummer.");
                mb.exec();
            }else
            {
                this->close();
            }
        }else if(Modus == MODUS_MITARB_EDIT)        {
            bool ok = true;
            if(Mitarb->set_vorname(nr, vona))//wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Der Vorname konnte nicht geändert werden.");
                mb.exec();
                ok = false;
            }
            if(Mitarb->set_nachname(nr, nana))//wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Der Nachname konnte nicht geändert werden.");
                mb.exec();
                ok = false;
            }
            int tmp = Mitarb->set_idscanner(nr, idscan);
            if(tmp)//wenn es einen Fehler gab
            {
                QString msg;
                msg = "Die Scanner-ID konnte nicht geändert werden.\n";
                if(tmp == 1)
                {
                    msg += "Mitarbeiter mir Personalnummer nr gibt es nicht";
                }else if(tmp == 2)
                {
                    msg += "Scanner-ID ist bereits vergeben";
                }
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                ok = false;
            }
            if(ok == true)
            {
                this->close();
            }
        }else
        {
            QString msg;
            msg = "Der Dialog wurde im Modus 0 aufgerufen.\n";
            msg += "Bitte wenden Sie sich an Ihren Administrator.";
            QMessageBox mb;
            mb.setText(msg);
            mb.setWindowTitle("Dialogaufruf fehlerhaft");
            mb.exec();
        }
    }
}
void Dialog_mitarb_einzeln::on_pushButton_abbrechen_clicked()
{
    this->close();
}







