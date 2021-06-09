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

    KoSt.initialisieren();
    Mitarb.initialisieren();

    connect(&Dlg_KoSt, SIGNAL(signal_kost(kostenstellen)), this, SLOT(slot_kost(kostenstellen)));
    connect(&Dlg_Mitarb, SIGNAL(signal_mitarb(mitarbeiter)), this, SLOT(slot_mitarb(mitarbeiter)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_kost(kostenstellen k)
{
    KoSt = k;
}
void MainWindow::slot_mitarb(mitarbeiter m)
{
    Mitarb = m;
}

void MainWindow::on_actionKostenstellen_triggered()
{
    Dlg_KoSt.show();
}
void MainWindow::on_actionMitarbeiter_triggered()
{
    Dlg_Mitarb.show();
}

