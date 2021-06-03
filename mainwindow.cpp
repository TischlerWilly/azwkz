#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prgpf.ordner_erstellen();
    KoSten.initialisieren();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionKostenstellen_triggered()
{
    Dlg_KoSt.show();
}
