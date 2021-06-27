#include "dialog_tageszettel.h"
#include "ui_dialog_tageszettel.h"

Dialog_tageszettel::Dialog_tageszettel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_tageszettel)
{
    ui->setupUi(this);
    Mitarb = NULL;
    Arbzeit = NULL;
    KoSt = NULL;
    ui->label_mitarb->setText("");
    ui->tableWidget_mitarb->setSortingEnabled(true);
}
Dialog_tageszettel::~Dialog_tageszettel()
{
    delete ui;
}
void Dialog_tageszettel::resizeEvent(QResizeEvent *event)
{
    int rand_un = 30;
    int rand_re = 10;
    ui->calendarWidget->move(2,2);
    int b_calendar = this->width()/8*3;
    if(b_calendar < 320)
    {
        b_calendar = 320;
    }else if(b_calendar > 400)
    {
        b_calendar = 400;
    }
    ui->calendarWidget->setFixedWidth(b_calendar);

    ui->tableWidget_mitarb->move(2,ui->calendarWidget->y()+ui->calendarWidget->height()+5);
    ui->tableWidget_mitarb->setFixedWidth(ui->calendarWidget->width());
    int h_tab_mitarb = this->height() - ui->tableWidget_mitarb->y() - rand_un;
    ui->tableWidget_mitarb->setFixedHeight(h_tab_mitarb);

    ui->label_mitarb->move(ui->calendarWidget->x()+ui->calendarWidget->width()+5,2);

    ui->tableWidget_import->move(ui->label_mitarb->x(),35);
    int h_tab_import = (this->height() - this->y())/8*5;
    ui->tableWidget_import->setFixedHeight(h_tab_import);
    int b_tab_import = this->width() - ui->tableWidget_import->x() - rand_re;
    int b_tab_tagzet = b_tab_import;
    int b_tab_kst = b_tab_import/8*3;
    if(b_tab_kst > 300)
    {
        b_tab_import = b_tab_import - b_tab_kst - 5;
        ui->tableWidget_kst->show();
        ui->tableWidget_kst->move(ui->tableWidget_import->x()+b_tab_import+5, \
                                  ui->tableWidget_import->y());
        ui->tableWidget_kst->setFixedWidth(b_tab_kst);
        ui->tableWidget_kst->setFixedHeight(ui->tableWidget_import->height());
    }else
    {
        ui->tableWidget_kst->hide();
    }
    ui->tableWidget_import->setFixedWidth(b_tab_import);

    b_tab_tagzet = b_tab_tagzet - ui->pushButton_tagzet_erstellen->width() - 5;
    int b_report = b_tab_tagzet;
    b_tab_tagzet = b_tab_tagzet / 8 * 5;
    b_report = b_report - b_tab_tagzet - 5;
    ui->tableWidget_tagzet->move(ui->label_mitarb->x(),ui->tableWidget_import->y()+ui->tableWidget_import->height()+5);
    int h_tab_tagzet = this->height() - ui->tableWidget_tagzet->y() - rand_un;
    ui->tableWidget_tagzet->setFixedHeight(h_tab_tagzet);
    ui->tableWidget_tagzet->setFixedWidth(b_tab_tagzet);

    ui->plainTextEdit_report->move(ui->tableWidget_tagzet->x()+b_tab_tagzet+5, ui->tableWidget_tagzet->y());
    ui->plainTextEdit_report->setFixedWidth(b_report);
    ui->plainTextEdit_report->setFixedHeight(ui->tableWidget_tagzet->height());

    ui->pushButton_tagzet_erstellen->move(ui->plainTextEdit_report->x()+b_report+5, ui->tableWidget_tagzet->y());

    QDialog::resizeEvent(event);
}

void Dialog_tageszettel::set_Mitarb(mitarbeiter *m)
{
    Mitarb = m;
    if(Arbzeit != NULL)
    {
        Arbzeit->set_MitArb(m);
    }
    update_tab_mitarb();
}
void Dialog_tageszettel::set_Arbzeit(arbeitszeiten *az)
{
    Arbzeit = az;
}
void Dialog_tageszettel::set_KoSt(kostenstellen *kst)
{
    KoSt = kst;
    if(Arbzeit != NULL)
    {
        Arbzeit->set_KoSt(kst);
    }
    update_tab_kost();
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
                if(KoSt != NULL)
                {
                    for(int i=0;i<Tab_arbzeit.anz_zeilen();i++)
                    {
                        QString nr  = Tab_arbzeit.wert(i,INDEX_ARBZEIT_KST);
                        QString bez = KoSt->bez(nr);
                        QString anzeigetext;
                        anzeigetext = nr;
                        anzeigetext += "   ";
                        anzeigetext += bez;
                        Tab_arbzeit.set_wert(i, INDEX_ARBZEIT_KST, anzeigetext);
                    }
                }
                ui->tableWidget_import->clear();
                ui->tableWidget_import->setColumnCount(Tab_arbzeit.anz_spalten());//Spaltenanzahl
                ui->tableWidget_import->setRowCount(Tab_arbzeit.anz_zeilen());//Zeilenanzahl
                ui->tableWidget_import->setHorizontalHeaderLabels(Tab_arbzeit.tabkopf().qstringlist());
                ui->tableWidget_import->setColumnWidth(INDEX_ARBZEIT_KST, 300);//Pers-Nr.
                bool sortieren_aktiv = ui->tableWidget_import->isSortingEnabled();
                ui->tableWidget_import->setSortingEnabled(false);
                for(int i=0;i<Tab_arbzeit.anz_zeilen();i++)
                {
                    for(int ii=0;ii<Tab_arbzeit.anz_spalten();ii++)
                    {
                        ui->tableWidget_import->setItem(i,ii,new QTableWidgetItem(Tab_arbzeit.wert(i,ii)));
                        if(Tab_arbzeit.wert(i,INDEX_ARBZEIT_KST).contains("000"))
                        {
                            ui->tableWidget_import->item(i,ii)->setBackground(Qt::gray);
                        }
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
void Dialog_tageszettel::update_tab_kost()
{
    if(KoSt != NULL)
    {
        bool sorting_enabled = ui->tableWidget_kst->isSortingEnabled();
        ui->tableWidget_kst->setSortingEnabled(false);
        //interne Tabelle:
        Tab_kst.clear();
        Tab_kst = *KoSt->tabelle();
        Tab_kst.sortieren_double(INDEX_KOST_NUMMER);
        //ui:
        ui->tableWidget_kst->clear();
        ui->tableWidget_kst->setColumnCount(Tab_kst.anz_spalten());//Spaltenanzahl
        ui->tableWidget_kst->setRowCount(Tab_kst.anz_zeilen());//Zeilenanzahl
        ui->tableWidget_kst->setHorizontalHeaderLabels(Tab_kst.tabkopf().qstringlist());
        ui->tableWidget_kst->setColumnWidth(0, 80);//Nr.
        ui->tableWidget_kst->setColumnWidth(1, 400);//Bez
        //Tabelle anzeigen
        for(int i=0;i<Tab_kst.anz_zeilen();i++)
        {
            for(int ii=0;ii<=Tab_kst.anz_spalten();ii++)
            {
                ui->tableWidget_kst->setItem(i,ii, new QTableWidgetItem(Tab_kst.wert(i,ii)));
            }
        }
        ui->tableWidget_kst->setSortingEnabled(sorting_enabled);
    }
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

void Dialog_tageszettel::on_pushButton_tagzet_erstellen_clicked()
{
    if(!Tab_mitarb.isEmpty() && Arbzeit != NULL && KoSt != NULL)
    {
        int row = ui->tableWidget_mitarb->currentRow();
        if(row >= 0)
        {
            QString idscan = Tab_mitarb.wert(row, INDEX_MITARB_IDSCANNER);
            if(!idscan.isEmpty())
            {
                QDate datum = ui->calendarWidget->selectedDate();
                Arbzeit->import();
                QString report;
                Arbzeit->set_MitArb(Mitarb);
                Tab_tagzet = Arbzeit->tagzet(idscan, datum, report);
                ui->plainTextEdit_report->setPlainText(report);
                ui->tableWidget_tagzet->clear();
                ui->tableWidget_tagzet->setColumnCount(Tab_tagzet.anz_spalten());//Spaltenanzahl
                ui->tableWidget_tagzet->setRowCount(Tab_tagzet.anz_zeilen());//Zeilenanzahl
                ui->tableWidget_tagzet->setHorizontalHeaderLabels(Tab_tagzet.tabkopf().qstringlist());
                ui->tableWidget_tagzet->setColumnWidth(INDEX_ARBZEIT_KST, 300);//Pers-Nr.
                bool sortieren_aktiv = ui->tableWidget_tagzet->isSortingEnabled();
                ui->tableWidget_import->setSortingEnabled(false);
                for(int i=0;i<Tab_tagzet.anz_zeilen();i++)
                {
                    for(int ii=0;ii<Tab_tagzet.anz_spalten();ii++)
                    {
                        ui->tableWidget_tagzet->setItem(i,ii,new QTableWidgetItem(Tab_tagzet.wert(i,ii)));
                    }
                }
                ui->tableWidget_tagzet->setSortingEnabled(sortieren_aktiv);
            }
        }
    }
}
