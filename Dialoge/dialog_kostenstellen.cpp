#include "dialog_kostenstellen.h"
#include "ui_dialog_kostenstellen.h"

Dialog_Kostenstellen::Dialog_Kostenstellen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Kostenstellen)
{
    ui->setupUi(this);
    ui->tableWidget_kost->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setWindowTitle("Kostenstellen verwalten");
    this->setModal(true);
}
Dialog_Kostenstellen::~Dialog_Kostenstellen()
{
    delete ui;
}
void Dialog_Kostenstellen::showEvent(QShowEvent *e)
{
    KoSt.initialisieren();
    update_tablewidget();
    QDialog::showEvent(e);
}
void Dialog_Kostenstellen::update_tablewidget()
{
    ui->tableWidget_kost->clear();
    ui->tableWidget_kost->setColumnCount(KoSt.tabelle()->anz_spalten());//Spaltenanzahl
    ui->tableWidget_kost->setRowCount(KoSt.tabelle()->anz_zeilen());//Zeilenanzahl
    ui->tableWidget_kost->setHorizontalHeaderLabels(KoSt.tabelle()->tabkopf().qstringlist());
    ui->tableWidget_kost->setColumnWidth(0,60);//nr
    ui->tableWidget_kost->setColumnWidth(1,200);//bez

    for(int i=0;i<KoSt.tabelle()->anz_zeilen();i++)
    {
        for(int ii=0;ii<=KoSt.tabelle()->anz_spalten();ii++)
        {
            ui->tableWidget_kost->setItem(i,ii, new QTableWidgetItem(KoSt.tabelle()->wert(i,ii)));
        }
    }
}
void Dialog_Kostenstellen::resizeEvent(QResizeEvent *event)
{
    //tu was

    QDialog::resizeEvent(event);
}
void Dialog_Kostenstellen::kostenstellen_sortieren()
{    
    KoSt.sortieren();
    update_tablewidget();
}
void Dialog_Kostenstellen::on_pushButton_abbrechen_clicked()
{
    this->close();
}
void Dialog_Kostenstellen::on_pushButton_ok_clicked()
{
    KoSt.speichern();
    QString msg;
    msg = "Die Änderungen werden nach dem nächsten Programmstart wirksam.";
    QMessageBox mb;
    mb.setText(msg);
    mb.setWindowTitle("Kostenstellen wurden gespeichert");
    mb.exec();
    this->hide();
}
void Dialog_Kostenstellen::on_tableWidget_kost_customContextMenuRequested(const QPoint &pos)
{
    QMenu m(this);
    QPoint mpos;
    mpos.setX(pos.x()+this->x());
    mpos.setY(pos.y()+this->y());
    m.addAction("Kostenstellen sortieren", this, SLOT(kostenstellen_sortieren()), 0) ;
    m.exec(this->mapFrom(this, mpos));
}

void Dialog_Kostenstellen::on_pushButton_neu_clicked()
{
    //Dialog aufrufen

    kostenstellen_sortieren();
}
