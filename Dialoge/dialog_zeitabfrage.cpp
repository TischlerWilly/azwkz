#include "dialog_zeitabfrage.h"
#include "ui_dialog_zeitabfrage.h"

Dialog_zeitabfrage::Dialog_zeitabfrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_zeitabfrage)
{
    ui->setupUi(this);
    connect(ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButton_abbrechen, SIGNAL(clicked()), this, SLOT(reject()));
}

Dialog_zeitabfrage::~Dialog_zeitabfrage()
{
    delete ui;
}

void Dialog_zeitabfrage::set_labeltext(QString msg)
{
    ui->label->setText(msg);
}
void Dialog_zeitabfrage::set_default_time(QTime t)
{
    ui->timeEdit->setTime(t);
}

QTime Dialog_zeitabfrage::zeit()
{
    return ui->timeEdit->time();
}





