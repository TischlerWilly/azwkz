#ifndef DIALOG_ZEITABFRAGE_H
#define DIALOG_ZEITABFRAGE_H

#include <QDialog>

namespace Ui {
class Dialog_zeitabfrage;
}

class Dialog_zeitabfrage : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_zeitabfrage(QWidget *parent = nullptr);
    ~Dialog_zeitabfrage();
    void set_labeltext(QString msg);
    void set_default_time(QTime t);

    QTime zeit();

private slots:

private:
    Ui::Dialog_zeitabfrage *ui;
};

#endif // DIALOG_ZEITABFRAGE_H
