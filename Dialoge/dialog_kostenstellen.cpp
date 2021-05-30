#include "dialog_kostenstellen.h"
#include "ui_dialog_kostenstellen.h"

Dialog_Kostenstellen::Dialog_Kostenstellen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Kostenstellen)
{
    ui->setupUi(this);
    KoSten.initialisieren();

    //Row = Zeile
    //Column = Spalte
    kostenstelle k;
    ui->tableWidget_kost->setColumnCount(2);//Spaltenanzahl
    ui->tableWidget_kost->setRowCount(2);//Zeilenanzahl
    text_zeilenweise tz;
    tz = k.tabkopf();
    ui->tableWidget_kost->setColumnWidth(0,60);
    ui->tableWidget_kost->setColumnWidth(1,200);
    ui->tableWidget_kost->setItem(0,0, new QTableWidgetItem(tz.zeile(1)));
    ui->tableWidget_kost->setItem(0,1, new QTableWidgetItem(tz.zeile(2)));

    text_zeilenweise tab = KoSten.tabelle();
    ui->tableWidget_kost->setRowCount(tab.zeilenanzahl()+1);//Zeilenanzahl
    text_zeilenweise zeile;
    zeile.set_trennzeichen(';');
    for(uint i=1;i<=tab.zeilenanzahl();i++)
    {
        zeile.set_text(tab.zeile(i));
        ui->tableWidget_kost->setItem(i,0, new QTableWidgetItem(zeile.zeile(1)));
        ui->tableWidget_kost->setItem(i,1, new QTableWidgetItem(zeile.zeile(2)));
    }
}

Dialog_Kostenstellen::~Dialog_Kostenstellen()
{
    delete ui;
}

void Dialog_Kostenstellen::on_pushButton_abbrechen_clicked()
{
    this->close();
}
