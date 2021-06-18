#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString titel;
    titel = "Arbeitszeitwerkzeug ";
    titel += PROGRAMMVERSION;
    this->setWindowTitle(titel);
    prgpf.ordner_erstellen();

    Dlg_azimport.setParent(this);
    Dlg_tagzet.setParent(this);
    Dlg_azimport.hide();

    KoSt.initialisieren();
    Mitarb.initialisieren();

    connect(&Dlg_KoSt, SIGNAL(signal_kost(kostenstellen)), this, SLOT(slot_kost(kostenstellen)));
    connect(&Dlg_Mitarb, SIGNAL(signal_mitarb(mitarbeiter)), this, SLOT(slot_mitarb(mitarbeiter)));

    Dlg_azimport.set_Mitarb(&Mitarb);
    Dlg_tagzet.set_Mitarb(&Mitarb);

    Dlg_azimport.set_Arbzeit(&Arbzeit);
    Dlg_tagzet.set_Arbzeit(&Arbzeit);

    Dlg_tagzet.set_KoSt(&KoSt);

    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Dlg_azimport.move(0,20);
    Dlg_azimport.setFixedSize(this->width(), this->height());

    Dlg_tagzet.move(0,20);
    Dlg_tagzet.setFixedSize(this->width(), this->height());

    QMainWindow::resizeEvent(event);
}
void MainWindow::slot_kost(kostenstellen k)
{
    KoSt = k;
}
void MainWindow::slot_mitarb(mitarbeiter m)
{
    Mitarb = m;
    Dlg_azimport.set_Mitarb(&Mitarb);
}
void MainWindow::on_actionKostenstellen_triggered()
{
    Dlg_KoSt.show();
}
void MainWindow::on_actionMitarbeiter_triggered()
{
    Dlg_Mitarb.show();
}
void MainWindow::on_actionTageszettel_triggered()
{
    Dlg_azimport.hide();
    Dlg_tagzet.show();
}
void MainWindow::on_actionImport_Uebersicht_triggered()
{
    Dlg_tagzet.hide();
    Dlg_azimport.show();
}













