#include "dialog_mitarbeiter.h"
#include "ui_dialog_mitarbeiter.h"

Dialog_Mitarbeiter::Dialog_Mitarbeiter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Mitarbeiter)
{
    ui->setupUi(this);
    ui->tableWidget_mitarb->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setWindowTitle("Kostenstellen verwalten");
    this->setModal(true);
    //this->setFixedWidth(500);
}
Dialog_Mitarbeiter::~Dialog_Mitarbeiter()
{
    delete ui;
}
void Dialog_Mitarbeiter::showEvent(QShowEvent *e)
{
    Mitarb.initialisieren();
    update_tablewidget();
    QDialog::showEvent(e);
}
void Dialog_Mitarbeiter::resizeEvent(QResizeEvent *event)
{


    QDialog::resizeEvent(event);
}
void Dialog_Mitarbeiter::mitarb_sortieren()
{
    Mitarb.sortieren();
    update_tablewidget();
}
void Dialog_Mitarbeiter::on_pushButton_ok_clicked()
{
    Mitarb.speichern();
    this->hide();
    emit(signal_mitarb(Mitarb));
}
void Dialog_Mitarbeiter::on_pushButton_abbrechen_clicked()
{
    this->close();
}
void Dialog_Mitarbeiter::on_pushButton_neu_clicked()
{

}
void Dialog_Mitarbeiter::on_pushButton_edit_clicked()
{

}
void Dialog_Mitarbeiter::on_pushButton_entfernen_clicked()
{

}
void Dialog_Mitarbeiter::on_tableWidget_kost_customContextMenuRequested(const QPoint &pos)
{
    QMenu m(this);
    QPoint mpos;
    mpos.setX(pos.x()+this->x());
    mpos.setY(pos.y()+this->y());
    m.addAction("Mitarbeiterliste sortieren", this, SLOT(mitarb_sortieren()), 0) ;
    m.exec(this->mapFrom(this, mpos));
}
void Dialog_Mitarbeiter::update_tablewidget()
{
    ui->tableWidget_mitarb->clear();
    ui->tableWidget_mitarb->setColumnCount(Mitarb.tabelle()->anz_spalten());//Spaltenanzahl
    ui->tableWidget_mitarb->setRowCount(Mitarb.tabelle()->anz_zeilen());//Zeilenanzahl
    ui->tableWidget_mitarb->setHorizontalHeaderLabels(Mitarb.tabelle()->tabkopf().qstringlist());
    ui->tableWidget_mitarb->setColumnWidth(0,60);//Pers.Nr.
    ui->tableWidget_mitarb->setColumnWidth(1,300);//Vorname
    ui->tableWidget_mitarb->setColumnWidth(2,300);//Nachname
    ui->tableWidget_mitarb->setColumnWidth(3,100);//ID-Scanner

    for(int i=0;i<Mitarb.tabelle()->anz_zeilen();i++)
    {
        for(int ii=0;ii<=Mitarb.tabelle()->anz_spalten();ii++)
        {
            ui->tableWidget_mitarb->setItem(i,ii, new QTableWidgetItem(Mitarb.tabelle()->wert(i,ii)));
        }
    }
}




