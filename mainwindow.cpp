#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prgpf.ordner_erstellen();
    KoSt.initialisieren();

    connect(&Dlg_KoSt, SIGNAL(signal_kost(kostenstellen)), this, SLOT(slot_kost(kostenstellen)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionKostenstellen_triggered()
{
    Dlg_KoSt.show();
}

void MainWindow::slot_kost(kostenstellen k)
{
    KoSt = k;
}
