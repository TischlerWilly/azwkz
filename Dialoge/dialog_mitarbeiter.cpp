#include "dialog_mitarbeiter.h"
#include "ui_dialog_mitarbeiter.h"

Dialog_Mitarbeiter::Dialog_Mitarbeiter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Mitarbeiter)
{
    ui->setupUi(this);
}

Dialog_Mitarbeiter::~Dialog_Mitarbeiter()
{
    delete ui;
}
