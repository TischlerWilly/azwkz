#include "dialog_kostenstelle.h"
#include "ui_dialog_kostenstelle.h"

Dialog_kostenstelle::Dialog_kostenstelle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_kostenstelle)
{
    ui->setupUi(this);
    KoSt = NULL;
    Modus = 0;
}

Dialog_kostenstelle::~Dialog_kostenstelle()
{
    delete ui;
}
void Dialog_kostenstelle::set_KoSt(kostenstellen *k)
{
    KoSt = k;
}
void Dialog_kostenstelle::set_Modus_neu()
{
    Modus = MODUS_KST_NEU;
    ui->spinBox_nr->setEnabled(true);
}
void Dialog_kostenstelle::set_Modus_edit()
{
    Modus = MODUS_KST_EDIT;
    ui->spinBox_nr->setDisabled(true);
}
void Dialog_kostenstelle::set_akt_kost(QString nr)
{
    if(KoSt == NULL)
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
        liste_QString lqs = KoSt->zeile_nr(nr);
        ui->spinBox_nr->setValue(lqs.wert(INDEX_KOST_NUMMER).toInt());
        ui->lineEdit_bez->setText(lqs.wert(INDEX_KOST_BEZEICHUNG));
    }
}
void Dialog_kostenstelle::on_pushButton_ok_clicked()
{
    liste_QString lqs;
    lqs.anhaengen(int_to_qstring(ui->spinBox_nr->value()));
    if(ui->lineEdit_bez->text().isEmpty())
    {
        QMessageBox mb;
        mb.setText("Bitte geben Sie noch eine Bezeichung ein.");
        mb.exec();
    }else
    {
        lqs.anhaengen(ui->lineEdit_bez->text());
        if(Modus == MODUS_KST_NEU)
        {
            if(KoSt->add(lqs))//Wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Diese Kostenstelle gibt es bereits.\nBitten wählen Sie eine andere Nummer.");
                mb.exec();
            }else
            {
                this->close();
            }
        }else if(Modus == MODUS_KST_EDIT)
        {
            QString nr = int_to_qstring(ui->spinBox_nr->value());
            QString bez = ui->lineEdit_bez->text();
            if(KoSt->set_bez(nr, bez))//wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Die Bezeichnung der Kostenstelle konnte nicht geändert werden.");
                mb.exec();
            }else
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

void Dialog_kostenstelle::on_pushButton_abbrechen_clicked()
{
    this->close();
}
