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
void Dialog_azimport::resizeEvent(QResizeEvent *event)
{
    int b_gesamt = this->width()-5;
    int b_label = 30;
    int b_dateedit = ui->dateEdit_bis->width();
    int b_btn = ui->pushButton_import->width();
    int b_combox = b_gesamt - 2*b_label - 2*b_dateedit -b_btn - 5*5;
    if(b_combox > 300)
    {
        b_combox = 300;
    }
    ui->comboBox_mitarb->move(2,2);
    ui->comboBox_mitarb->setFixedWidth(b_combox);

    ui->label_von->move(ui->comboBox_mitarb->x()+b_combox+5,2);
    ui->label_von->setFixedWidth(b_label);

    ui->dateEdit_von->move(ui->label_von->x()+b_label+5,2);

    ui->label_bis->move(ui->dateEdit_von->x()+ui->dateEdit_von->width()+5,2);
    ui->label_bis->setFixedWidth(b_label);

    ui->dateEdit_bis->move(ui->label_bis->x()+b_label+5,2);

    ui->pushButton_import->move(ui->dateEdit_bis->x()+ui->dateEdit_bis->width()+5,2);

    ui->tableWidget->move(2,ui->comboBox_mitarb->y()+ui->comboBox_mitarb->height()+2);
    ui->tableWidget->setFixedWidth(b_gesamt);
    ui->tableWidget->setFixedHeight(this->height() -2-ui->comboBox_mitarb->height()-2-25);

    QDialog::resizeEvent(event);
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









