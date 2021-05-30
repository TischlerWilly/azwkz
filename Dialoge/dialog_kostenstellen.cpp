#include "dialog_kostenstellen.h"
#include "ui_dialog_kostenstellen.h"

Dialog_Kostenstellen::Dialog_Kostenstellen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Kostenstellen)
{
    ui->setupUi(this);    
}

void Dialog_Kostenstellen::showEvent(QShowEvent *e)
{
    KoSten.initialisieren();
    kostenstelle k;    
    text_zeilenweise tz;
    tz = k.tabkopf();
    ui->tableWidget_kost->setColumnCount(tz.zeilenanzahl());//Spaltenanzahl
    ui->tableWidget_kost->setRowCount(1);//Zeilenanzahl
    QStringList tabkopf;
    for(uint i=1;i<=tz.zeilenanzahl();i++)
    {
        tabkopf << tz.zeile(i);
    }
    ui->tableWidget_kost->setHorizontalHeaderLabels(tabkopf);
    ui->tableWidget_kost->setColumnWidth(0,60);//nr
    ui->tableWidget_kost->setColumnWidth(1,200);//bez

    text_zeilenweise tab = KoSten.tabelle();
    text_zeilenweise zeile;
    zeile.set_trennzeichen(';');
    for(uint i=1;i<=tab.zeilenanzahl();i++)
    {
        zeile.set_text(tab.zeile(i));
        for(uint ii=1;ii<=zeile.zeilenanzahl();ii++)
        {
            ui->tableWidget_kost->setItem(i-1,ii-1, new QTableWidgetItem(zeile.zeile(ii)));
        }
        if(i==tab.zeilenanzahl())
        {//Ein zusätzlicher durchlauf der leere items einfügt:
            for(uint ii=1;ii<=zeile.zeilenanzahl();ii++)
            {
                ui->tableWidget_kost->setItem(i,ii-1, new QTableWidgetItem(""));
            }
        }
    }
   QDialog::showEvent(e);
}
Dialog_Kostenstellen::~Dialog_Kostenstellen()
{
    delete ui;
}
void Dialog_Kostenstellen::on_pushButton_abbrechen_clicked()
{
    this->close();
}
void Dialog_Kostenstellen::on_pushButton_ok_clicked()
{
    KoSten.speichern();
    QString msg;
    msg = "Die Änderungen werden nach dem nächsten Programmstart wirksam.";
    QMessageBox mb;
    mb.setText(msg);
    mb.setWindowTitle("Kostenstellen wurden gespeichert");
    mb.exec();
    this->hide();
}
void Dialog_Kostenstellen::on_tableWidget_kost_cellChanged(int row, int column)
{
    if(column == 0)//nr
    {//neue Zeile in Tabelle einfügen und mit items füllen:
        QString nr;
        nr = ui->tableWidget_kost->item(row, column)->text();
        if(!nr.isEmpty())
        {
            if(nr.toInt() > 0)
            {
                ui->tableWidget_kost->setRowCount(ui->tableWidget_kost->rowCount()+1);
                //...
                //in Kostenstellen speichern


                for(int i=0;i<=ui->tableWidget_kost->columnCount();i++)
                {
                    ui->tableWidget_kost->setItem(ui->tableWidget_kost->rowCount(),i, new QTableWidgetItem(""));
                }
            }else
            {
                QMessageBox mb;
                mb.setText("Bitte nur Ziffern verwenden!");
                mb.setWindowTitle("Kostenstelle erstellen");
                mb.exec();
                ui->tableWidget_kost->item(row, column)->setText("");
            }
        }
    }else if(column == 1)//bez
    {
        QString bez;
        bez = ui->tableWidget_kost->item(row, column)->text();
        QString nr;
        nr = ui->tableWidget_kost->item(row, 0)->text();
        if(!bez.isEmpty())
        {
            if(nr.isEmpty())
            {
                QMessageBox mb;
                mb.setText("Bitte zuerst eine Kostenstellennummer eintragen!");
                mb.exec();
                ui->tableWidget_kost->item(row, column)->setText("");
            }else
            {//Bez ändern:
                KoSten.set_bez(nr, bez);
            }
        }
    }
}
