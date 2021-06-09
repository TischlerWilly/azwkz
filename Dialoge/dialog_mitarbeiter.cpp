#include "dialog_mitarbeiter.h"
#include "ui_dialog_mitarbeiter.h"

Dialog_Mitarbeiter::Dialog_Mitarbeiter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Mitarbeiter)
{
    ui->setupUi(this);
    ui->tableWidget_mitarb->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setWindowTitle("Mitarbeiter verwalten");
    this->setModal(true);
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
    ui->tableWidget_mitarb->move(2,2);
    ui->tableWidget_mitarb->setFixedWidth(this->width()-100);
    ui->tableWidget_mitarb->setFixedHeight(this->height()-30);

    ui->pushButton_ok->move(2+ui->tableWidget_mitarb->width()/2-2-ui->pushButton_ok->width(), this->height()-25);
    ui->pushButton_abbrechen->move(ui->pushButton_ok->x()+ui->pushButton_ok->width()+5, ui->pushButton_ok->y());

    ui->pushButton_neu->move(this->width()-90, 2);
    ui->pushButton_edit->move(this->width()-90, 2+25+2);
    ui->pushButton_entfernen->move(this->width()-90, 2+(25+2)*2);

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
    Dialog_mitarb_einzeln dlg;
    dlg.setWindowTitle("Mitarbeiter anlegen");
    dlg.set_Mitarb(&Mitarb);
    dlg.set_Modus_neu();
    dlg.exec();
    mitarb_sortieren();
}
void Dialog_Mitarbeiter::on_pushButton_edit_clicked()
{
    int row = ui->tableWidget_mitarb->currentRow();
    if(row >= 0)
    {
        QString nr = Mitarb.tabelle()->wert(row, INDEX_MITARB_NUMMER);
        Dialog_mitarb_einzeln dlg;
        dlg.setWindowTitle("Mitarbeiter bearbeiten");
        dlg.set_Mitarb(&Mitarb);
        dlg.set_Modus_edit();
        dlg.set_akt_mitarb(nr);
        dlg.exec();
        mitarb_sortieren();
    }else
    {
        QString msg;
        msg = "Bitte klicken Sie zuvor einen Mitarbeiter in der Tabelle an.";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Mitarbeiter bearbeiten");
        mb.exec();
    }
}
void Dialog_Mitarbeiter::on_pushButton_entfernen_clicked()
{
    int row = ui->tableWidget_mitarb->currentRow();
    if(row >= 0)
    {
        //Sicherheitsbafrage:
        QString msg;
        msg = "Wollen Sie den Mitarbeiter\n";
        msg += Mitarb.tabelle()->wert(row, INDEX_MITARB_NUMMER);
        msg += " | ";
        msg += Mitarb.tabelle()->wert(row, INDEX_MITARB_VORNAME);
        msg += " | ";
        msg += Mitarb.tabelle()->wert(row, INDEX_MITARB_NACHNAME);
        msg += "\n wirklich löschen?";
        QMessageBox mb;
        mb.setWindowTitle("Kotarbeiter löschen");
        mb.setText(msg);
        mb.setStandardButtons(QMessageBox::Yes);
        mb.addButton(QMessageBox::No);
        mb.setDefaultButton(QMessageBox::No);
        int mb_returnwert = mb.exec();
        if(mb_returnwert == QMessageBox::Yes)
        {
            QString nr = Mitarb.tabelle()->wert(row, INDEX_MITARB_NUMMER);
            if(Mitarb.del(nr))//Wenn es einen Fehler gab
            {
                QMessageBox mb;
                mb.setText("Der Mitarbeiter konnte nicht gelöscht werden.");
                mb.exec();
            }else
            {
                mitarb_sortieren();
            }
        }
    }else
    {
        QString msg;
        msg = "Bitte klicken Sie zuvor einen Mitarbeiter in der Tabelle an.";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Mitarbeiter bearbeiten");
        mb.exec();
    }
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
    ui->tableWidget_mitarb->setColumnWidth(1,150);//Vorname
    ui->tableWidget_mitarb->setColumnWidth(2,150);//Nachname
    ui->tableWidget_mitarb->setColumnWidth(3,100);//ID-Scanner

    for(int i=0;i<Mitarb.tabelle()->anz_zeilen();i++)
    {
        for(int ii=0;ii<=Mitarb.tabelle()->anz_spalten();ii++)
        {
            ui->tableWidget_mitarb->setItem(i,ii, new QTableWidgetItem(Mitarb.tabelle()->wert(i,ii)));
        }
    }
}




