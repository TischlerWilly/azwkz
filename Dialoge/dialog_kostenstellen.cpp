#include "dialog_kostenstellen.h"
#include "ui_dialog_kostenstellen.h"

Dialog_Kostenstellen::Dialog_Kostenstellen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Kostenstellen)
{
    ui->setupUi(this);
    tabellenupdate = false; //Tabelle wird gerade nicht neu aufgebaut
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
    daten_vor_aenderung.clear();
    ui->tableWidget_kost->clear();
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

    text_zeilenweise tab = KoSten.tabelle_tz();
    text_zeilenweise zeile;
    zeile.set_trennzeichen(';');
    for(uint i=1;i<=tab.zeilenanzahl();i++)
    {
        zeile.set_text(tab.zeile(i));
        for(uint ii=1;ii<=zeile.zeilenanzahl();ii++)
        {
            tabellenupdate = true;
            ui->tableWidget_kost->setItem(i-1,ii-1, new QTableWidgetItem(zeile.zeile(ii)));
        }
        if(i==tab.zeilenanzahl())
        {//Ein zusätzlicher durchlauf der leere items einfügt:
            for(uint ii=1;ii<=zeile.zeilenanzahl();ii++)
            {
                tabellenupdate = true;
                ui->tableWidget_kost->setItem(i,ii-1, new QTableWidgetItem(""));
            }
        }
    }
   QDialog::showEvent(e);
}
void Dialog_Kostenstellen::resizeEvent(QResizeEvent *event)
{
    //tu was

    QDialog::resizeEvent(event);
}
void Dialog_Kostenstellen::zeile_anhaengen()
{
    ui->tableWidget_kost->setRowCount(ui->tableWidget_kost->rowCount()+1);
    for(int i=0;i<=ui->tableWidget_kost->columnCount();i++)
    {
        ui->tableWidget_kost->setItem(ui->tableWidget_kost->rowCount(),i, new QTableWidgetItem(""));
    }
}
void Dialog_Kostenstellen::kostenstellen_sortieren()
{
    KoSten.sortieren();
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
        if(ui->tableWidget_kost->item(row, column))
        {
            nr = ui->tableWidget_kost->item(row, column)->text();
        }
        if(!nr.isEmpty())
        {
            if(nr.toInt() > 0)
            {
                kostenstelle k;
                k.set_nr(nr);
                if(tabellenupdate == false)
                {
                    if(KoSten.add(k))
                    {
                        zeile_anhaengen();
                    }else
                    {
                        QString msg;
                        msg ="Kostenstelle konnte nicht angelegt werden.";
                        msg += "\n";
                        msg += "Eventuell ist diese Kostenstellennummer bereits vergeben.";
                        QMessageBox mb;
                        mb.setText(msg);
                        mb.setWindowTitle("Kostenstelle anlegen");
                        mb.exec();
                        if(ui->tableWidget_kost->item(row, column))
                        {
                            ui->tableWidget_kost->item(row, column)->setText("");
                        }
                    }
                }else
                {
                    bool istleer = false;
                    int zeilenanzahl = ui->tableWidget_kost->rowCount();
                    int spaltenanzahl = ui->tableWidget_kost->columnCount();
                    for(int i=0;i<spaltenanzahl;i++)//alle Spalten in einer Zeile prüfen
                    {
                        //column = Spalten
                        //ui->tableWidget_kost->item(row, column)
                        if(ui->tableWidget_kost->item(zeilenanzahl-1, i))
                        {
                            if(ui->tableWidget_kost->item(zeilenanzahl-1, i)->text().isEmpty())
                            {
                                istleer = true;
                            }
                        }
                    }
                    if(istleer == false)
                    {
                        zeile_anhaengen();
                    }
                }
            }else
            {
                QMessageBox mb;
                mb.setText("Bitte nur Ziffern verwenden!");
                mb.setWindowTitle("Kostenstelle erstellen");
                mb.exec();
                if(ui->tableWidget_kost->item(row, column))
                {
                    ui->tableWidget_kost->item(row, column)->setText("");
                }
            }
        }else
        {
            if(!daten_vor_aenderung.isEmpty() && (row != ui->tableWidget_kost->rowCount()-1))
            {
                kostenstelle k = KoSten.kost(daten_vor_aenderung);
                QString msg;
                msg = "Möchten Sie die Kostenstelle\n";
                msg += k.nr();
                msg += " / ";
                msg += k.bez();
                msg += "\n";
                msg += "wirklich löschen?";
                QMessageBox mb;
                mb.setWindowTitle("Kostenstelle löschen");
                mb.setText(msg);
                mb.setStandardButtons(QMessageBox::Yes);
                mb.addButton(QMessageBox::No);
                mb.setDefaultButton(QMessageBox::No);
                int mb_returnwert = mb.exec();
                if(mb_returnwert == QMessageBox::Yes)
                {                    
                    KoSten.del(k);
                    ui->tableWidget_kost->removeRow(row);
                }else
                {
                    tabellenupdate = true;
                    if(ui->tableWidget_kost->item(row, column))
                    {
                        ui->tableWidget_kost->item(row, column)->setText(daten_vor_aenderung);
                    }
                }
                daten_vor_aenderung.clear();
            }
        }
    }else if(column == 1)//bez
    {
        QString bez;
        if(ui->tableWidget_kost->item(row, column))
        {
            bez = ui->tableWidget_kost->item(row, column)->text();
        }
        QString nr;
        if(ui->tableWidget_kost->item(row, 0))
        {
            nr = ui->tableWidget_kost->item(row, 0)->text();
        }
        if(!bez.isEmpty())
        {
            if(nr.isEmpty())
            {
                QMessageBox mb;
                mb.setText("Bitte zuerst eine Kostenstellennummer eintragen!");
                mb.exec();
                if(ui->tableWidget_kost->item(row, column))
                {
                    ui->tableWidget_kost->item(row, column)->setText("");
                }
            }else
            {//Bez ändern:
                KoSten.set_bez(nr, bez);
            }
        }
    }
    tabellenupdate = false;
}
void Dialog_Kostenstellen::on_tableWidget_kost_itemSelectionChanged()
{
    if(ui->tableWidget_kost->currentItem())
    {
        daten_vor_aenderung = ui->tableWidget_kost->currentItem()->text();
    }
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
