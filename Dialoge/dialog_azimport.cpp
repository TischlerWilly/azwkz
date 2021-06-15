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
    if(Arbzeit != NULL)
    {
        Arbzeit->import();
        Arbzeit->tabelle()->sortieren_double(INDEX_ARBZEIT_IDSCAN);
        Arbzeit->tabelle()->sortieren_datum(INDEX_ARBZEIT_TAG);
        //Arbzeit->tabelle()->sortieren_zeit(INDEX_ARBZEIT_UHRZEIT);
        //Arbzeit->tabelle()->sortieren_double(INDEX_ARBZEIT_KST);
    }
    update_tabelle();
}
void Dialog_azimport::on_comboBox_mitarb_currentIndexChanged(const QString &arg1)
{
    update_tabelle();
}
void Dialog_azimport::on_dateEdit_von_userDateChanged(const QDate &date)
{
    update_tabelle();
}
void Dialog_azimport::on_dateEdit_bis_userDateChanged(const QDate &date)
{
    update_tabelle();
}
void Dialog_azimport::update_tabelle()
{
    if((Arbzeit != NULL) && (Mitarb != NULL))
    {
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(Arbzeit->tabelle()->anz_spalten());//Spaltenanzahl
        ui->tableWidget->setRowCount(Arbzeit->tabelle()->anz_zeilen());//Zeilenanzahl
        liste_QString tabkopf = Arbzeit->tabelle()->tabkopf();
        tabkopf.ersaetzen(INDEX_ARBZEIT_IDSCAN, "Mitarbeiter");
        ui->tableWidget->setHorizontalHeaderLabels(tabkopf.qstringlist());
        bool sorting_enabled = ui->tableWidget->isSortingEnabled();
        ui->tableWidget->setSortingEnabled(false);
        //Tabelle filtern:
        tabelle_qstring tab;
        QString idscan;
        if(ui->comboBox_mitarb->currentText() != "Alle")
        {
            QString nr = text_links(ui->comboBox_mitarb->currentText(), " ");
            if(nr.toInt() != 0)
            {
                idscan = Mitarb->zeile_nr(nr).wert(INDEX_MITARB_IDSCANNER);
            }
            if(idscan.isEmpty())
            {
                idscan = "void";
            }
        }
        tab = Arbzeit->tabelle(idscan, ui->dateEdit_von->date(), ui->dateEdit_bis->date());
        ui->tableWidget->setRowCount(tab.anz_zeilen());//Zeilenanzahl
        //Tabelle anzeigen
        for(int i=0;i<tab.anz_zeilen();i++)
        {
            for(int ii=0;ii<=tab.anz_spalten();ii++)
            {
                ui->tableWidget->setItem(i,ii, new QTableWidgetItem(tab.wert(i,ii)));
            }
            QString idscan = tab.wert(i,INDEX_ARBZEIT_IDSCAN);
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
        ui->tableWidget->setSortingEnabled(sorting_enabled);
    }
}









