#include "dialog_kostenstellen.h"
#include "ui_dialog_kostenstellen.h"

Dialog_Kostenstellen::Dialog_Kostenstellen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Kostenstellen)
{
    ui->setupUi(this);

    //Row = Zeile
    //Column = Spalte
    kostenstelle k;
    ui->tableWidget_kost->setColumnCount(2);
    ui->tableWidget_kost->setRowCount(2);
    text_zeilenweise tz;
    tz = k.tabkopf();
    ui->tableWidget_kost->setColumnWidth(0,60);
    ui->tableWidget_kost->setColumnWidth(1,200);
    ui->tableWidget_kost->setItem(0,0, new QTableWidgetItem(tz.zeile(1)));
    ui->tableWidget_kost->setItem(0,1, new QTableWidgetItem(tz.zeile(2)));
}

Dialog_Kostenstellen::~Dialog_Kostenstellen()
{
    delete ui;
}

void Dialog_Kostenstellen::on_pushButton_abbrechen_clicked()
{
    this->close();
}
