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
    this->setFixedWidth(500);
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
    ui->tableWidget_kost->setColumnWidth(1,300);//bez

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
    ui->tableWidget_kost->move(2,2);
    ui->tableWidget_kost->setFixedWidth(this->width()-100);
    ui->tableWidget_kost->setFixedHeight(this->height()-30);

    ui->pushButton_ok->move(2+ui->tableWidget_kost->width()/2-2-ui->pushButton_ok->width(), this->height()-25);
    ui->pushButton_abbrechen->move(ui->pushButton_ok->x()+ui->pushButton_ok->width()+5, ui->pushButton_ok->y());

    ui->pushButton_neu->move(this->width()-90, 2);
    ui->pushButton_edit->move(this->width()-90, 2+25+2);
    ui->pushButton_entfernen->move(this->width()-90, 2+(25+2)*2);

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
    this->hide();
    emit(signal_kost(KoSt));
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
    Dialog_kostenstelle dlg;
    dlg.setWindowTitle("Kostenstelle anlegen");
    dlg.set_KoSt(&KoSt);
    dlg.set_Modus_neu();
    dlg.exec();
    kostenstellen_sortieren();
}
void Dialog_Kostenstellen::on_pushButton_edit_clicked()
{
    int row = ui->tableWidget_kost->currentRow();
    if(row >= 0)
    {
        QString nr = KoSt.tabelle()->wert(row, INDEX_KOST_NUMMER);
        Dialog_kostenstelle dlg;
        dlg.setWindowTitle("Kostenstelle bearbeiten");
        dlg.set_KoSt(&KoSt);
        dlg.set_Modus_edit();
        dlg.set_akt_kost(nr);
        dlg.exec();
        kostenstellen_sortieren();
    }else
    {
        QString msg;
        msg = "Bitte klicken Sie zuvor eine Kostenstelle in der Tabelle an.";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Kostenstelle bearbeiten");
        mb.exec();
    }
}
void Dialog_Kostenstellen::on_pushButton_entfernen_clicked()
{
    int row = ui->tableWidget_kost->currentRow();
    if(row >= 0)
    {
        //Sicherheitsbafrage:
        QString msg;
        msg = "Wollen Sie die Kostenstelle\n";
        msg += KoSt.tabelle()->zeile(row).tz('\t').text();
        msg += "\n wirklich löschen?";
        QMessageBox mb;
        mb.setWindowTitle("Mostenstelle löschen");
        mb.setText(msg);
        mb.setStandardButtons(QMessageBox::Yes);
        mb.addButton(QMessageBox::No);
        mb.setDefaultButton(QMessageBox::No);
        int mb_returnwert = mb.exec();
        if(mb_returnwert == QMessageBox::Yes)
        {
            QString nr = KoSt.tabelle()->wert(row, INDEX_KOST_NUMMER);
            if(KoSt.del(nr))//Wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Die Kostenstelle konnte nicht gelöscht werden.");
                mb.exec();
            }else
            {
                kostenstellen_sortieren();
            }
        }
    }else
    {
        QString msg;
        msg = "Bitte klicken Sie zuvor eine Kostenstelle in der Tabelle an.";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Kostenstelle bearbeiten");
        mb.exec();
    }
}
