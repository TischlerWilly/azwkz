#include "dialog_tageszettel.h"
#include "ui_dialog_tageszettel.h"

Dialog_tageszettel::Dialog_tageszettel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_tageszettel)
{
    ui->setupUi(this);
    Mitarb = NULL;
    Arbzeit = NULL;
    ui->label_mitarb->setText("");
    ui->tableWidget_mitarb->setSortingEnabled(true);
}
Dialog_tageszettel::~Dialog_tageszettel()
{
    delete ui;
}
void Dialog_tageszettel::resizeEvent(QResizeEvent *event)
{


    QDialog::resizeEvent(event);
}
void Dialog_tageszettel::set_Mitarb(mitarbeiter *m)
{
    Mitarb = m;
    update_tab_mitarb();
}
void Dialog_tageszettel::update_tab_mitarb()
{
    if(Mitarb != NULL)
    {
        bool sorting_enabled = ui->tableWidget_mitarb->isSortingEnabled();
        ui->tableWidget_mitarb->setSortingEnabled(false);
        //interne Tabelle:
        Tab_mitarb.clear();
        Tab_mitarb = *Mitarb->tabelle();
        Tab_mitarb.sortieren_double(INDEX_MITARB_NUMMER);
        //ui:
        ui->tableWidget_mitarb->clear();
        ui->tableWidget_mitarb->setColumnCount(Tab_mitarb.anz_spalten());//Spaltenanzahl
        ui->tableWidget_mitarb->setRowCount(Tab_mitarb.anz_zeilen());//Zeilenanzahl
        ui->tableWidget_mitarb->setHorizontalHeaderLabels(Tab_mitarb.tabkopf().qstringlist());
        ui->tableWidget_mitarb->setColumnWidth(0, 50);//Pers-Nr.
        //Tabelle anzeigen
        for(int i=0;i<Tab_mitarb.anz_zeilen();i++)
        {
            for(int ii=0;ii<=Tab_mitarb.anz_spalten();ii++)
            {
                ui->tableWidget_mitarb->setItem(i,ii, new QTableWidgetItem(Tab_mitarb.wert(i,ii)));
            }
        }
        ui->tableWidget_mitarb->setSortingEnabled(sorting_enabled);
    }
}
void Dialog_tageszettel::update_label_mitarb()
{
    if(!Tab_mitarb.isEmpty())
    {
        int row = ui->tableWidget_mitarb->currentRow();
        if(row >= 0)
        {
            //Namen in Label schreiben:
            QString name;
            name = Tab_mitarb.wert(row, INDEX_MITARB_NUMMER);
            name += " ";
            name += Tab_mitarb.wert(row, INDEX_MITARB_VORNAME);
            name += " ";
            name += Tab_mitarb.wert(row, INDEX_MITARB_NACHNAME);
            ui->label_mitarb->setText(name);
        }
    }
}
void Dialog_tageszettel::update_tab_import()
{
    if(!Tab_mitarb.isEmpty() && Arbzeit != NULL)
    {
        int row = ui->tableWidget_mitarb->currentRow();
        if(row >= 0)
        {
            QString idscan = Tab_mitarb.wert(row, INDEX_MITARB_IDSCANNER);
            if(!idscan.isEmpty())
            {
                QDate datum = ui->calendarWidget->selectedDate();
                Arbzeit->import();
                Tab_arbzeit = Arbzeit->tabelle(idscan, datum, datum);
                ui->tableWidget_import->clear();
                ui->tableWidget_import->setColumnCount(Tab_arbzeit.anz_spalten());//Spaltenanzahl
                ui->tableWidget_import->setRowCount(Tab_arbzeit.anz_zeilen());//Zeilenanzahl
                ui->tableWidget_import->setHorizontalHeaderLabels(Tab_arbzeit.tabkopf().qstringlist());
                bool sortieren_aktiv = ui->tableWidget_import->isSortingEnabled();
                ui->tableWidget_import->setSortingEnabled(false);
                for(int i=0;i<Tab_arbzeit.anz_zeilen();i++)
                {
                    for(int ii=0;ii<Tab_arbzeit.anz_spalten();ii++)
                    {
                        ui->tableWidget_import->setItem(i,ii,new QTableWidgetItem(Tab_arbzeit.wert(i,ii)));
                    }
                }
                ui->tableWidget_import->setSortingEnabled(sortieren_aktiv);
            }else
            {
                ui->tableWidget_import->clear();
                Tab_arbzeit.clear();
            }
        }
    }
}
void Dialog_tageszettel::set_Arbzeit(arbeitszeiten *az)
{
    Arbzeit = az;
}
void Dialog_tageszettel::on_tableWidget_mitarb_cellClicked(int row, int column)
{
    update_label_mitarb();
    update_tab_import();
}
void Dialog_tageszettel::on_calendarWidget_clicked(const QDate &date)
{
    update_label_mitarb();
    update_tab_import();
}
