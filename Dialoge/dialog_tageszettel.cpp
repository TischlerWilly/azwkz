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
void Dialog_tageszettel::set_Arbzeit(arbeitszeiten *az)
{
    Arbzeit = az;
}
void Dialog_tageszettel::on_tableWidget_mitarb_cellClicked(int row, int column)
{
    if(!Tab_mitarb.isEmpty())
    {
        QString name;
        name = Tab_mitarb.wert(row, INDEX_MITARB_NUMMER);
        name += " ";
        name += Tab_mitarb.wert(row, INDEX_MITARB_VORNAME);
        name += " ";
        name += Tab_mitarb.wert(row, INDEX_MITARB_NACHNAME);
        ui->label_mitarb->setText(name);
    }
}
