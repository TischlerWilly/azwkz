#include "dialog_azimport.h"
#include "ui_dialog_azimport.h"

Dialog_azimport::Dialog_azimport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_azimport)
{
    ui->setupUi(this);
    Mitarb = NULL;
    Arbzeit = NULL;
    ui->dateEdit_bis->setDate(QDate::currentDate());
    ui->comboBox_mitarb->addItem("Alle");
}

Dialog_azimport::~Dialog_azimport()
{
    delete ui;
}
void Dialog_azimport::set_Mitarb(mitarbeiter *m)
{
    Mitarb = m;
    ui->comboBox_mitarb->clear();
    ui->comboBox_mitarb->addItem("Alle");
    if(Mitarb != NULL)
    {
        for(int i=0; i<Mitarb->tabelle()->anz_zeilen() ;i++)
        {
            QString eintrag;
            eintrag = Mitarb->tabelle()->wert(i,INDEX_MITARB_NUMMER);
            eintrag += " ";
            eintrag += Mitarb->tabelle()->wert(i,INDEX_MITARB_VORNAME);
            eintrag += " ";
            eintrag += Mitarb->tabelle()->wert(i,INDEX_MITARB_NACHNAME);
            ui->comboBox_mitarb->addItem(eintrag);
        }
    }
}
void Dialog_azimport::set_Arbzeit(arbeitszeiten *az)
{
    Arbzeit = az;
}
void Dialog_azimport::on_pushButton_import_clicked()
{
    prgpfade pf;
    QDir idir = pf.dir_import_az();
    liste_QString dateien = dateien_erfassen(idir);
    if(Arbzeit != NULL)
    {
        for(int i=0;i<dateien.count();i++)//Datei für Datei einlesen
        {
            QFile f(dateien.qstringlist().at(i));
            text_zeilenweise tz;
            if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QString msg;
                msg = "Fehler beim zugriff auf die Datei \"";
                msg += dateien.qstringlist().at(i);
                msg += "\"!";
                QMessageBox::warning(this,"Fehler",msg,QMessageBox::Ok);
            }else
            {
                tz.set_text(QString::fromLatin1(f.readAll()));
            }
            for(uint ii=2;ii<tz.zeilenanzahl();ii++)//Zeile für Zeile speichern
            {//Erst in 2. Zeile beginnen weil 1. Zeile Tabellenkpf ist
                text_zeilenweise zeile_tz;
                zeile_tz.set_trennzeichen('\t');
                zeile_tz.set_text(tz.zeile(ii));
                liste_QString zeile;
                QString idscan, tag, zeit, proj, kst;
                idscan = zeile_tz.zeile(4);
                tag = zeile_tz.zeile(5);
                zeit = zeile_tz.zeile(3);
                proj = zeile_tz.zeile(1);
                kst = zeile_tz.zeile(2);
                zeile.anhaengen(idscan);
                zeile.anhaengen(tag);
                zeile.anhaengen(text_links(zeit,"Uhr"));
                zeile.anhaengen(proj);
                zeile.anhaengen(kst);
                Arbzeit->add(zeile);
            }
        }
        Arbzeit->tabelle()->sortieren_zeit(INDEX_ARBZEIT_UHRZEIT);
        //Arbzeit->tabelle()->sortieren_datum(INDEX_ARBZEIT_TAG);
        //Arbzeit->tabelle()->sortieren_double(INDEX_ARBZEIT_IDSCAN);
        //Arbzeit->tabelle()->sortieren_double(INDEX_ARBZEIT_KST);
    }
    update_tabelle();
}
void Dialog_azimport::update_tabelle()
{
    if(Arbzeit != NULL)
    {
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(Arbzeit->tabelle()->anz_spalten());//Spaltenanzahl
        ui->tableWidget->setRowCount(Arbzeit->tabelle()->anz_zeilen());//Zeilenanzahl
        liste_QString tabkopf = Arbzeit->tabelle()->tabkopf();
        tabkopf.ersaetzen(INDEX_ARBZEIT_IDSCAN, "Mitarbeiter");
        ui->tableWidget->setHorizontalHeaderLabels(tabkopf.qstringlist());
        for(int i=0;i<Arbzeit->tabelle()->anz_zeilen();i++)
        {
            for(int ii=0;ii<=Arbzeit->tabelle()->anz_spalten();ii++)
            {
                ui->tableWidget->setItem(i,ii, new QTableWidgetItem(Arbzeit->tabelle()->wert(i,ii)));
            }
            QString idscan = Arbzeit->tabelle()->wert(i,INDEX_ARBZEIT_IDSCAN);
            if(Mitarb != NULL)
            {
                liste_QString mitarb = Mitarb->zeile_idscan(idscan);
                if(!mitarb.isEmpty())
                {
                    QString nr, vona, nana;
                    nr = mitarb.wert(INDEX_MITARB_NUMMER);
                    vona = mitarb.wert(INDEX_MITARB_VORNAME);
                    nana = mitarb.wert(INDEX_MITARB_NACHNAME);
                    QString tmp;
                    tmp = nr;
                    tmp += " ";
                    tmp += vona;
                    tmp += " ";
                    tmp += nana;
                    ui->tableWidget->item(i,0)->setText(tmp);
                }
            }
        }
    }
}







