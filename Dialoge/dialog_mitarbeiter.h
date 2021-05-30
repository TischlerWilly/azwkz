#ifndef DIALOG_MITARBEITER_H
#define DIALOG_MITARBEITER_H

#include <QDialog>

namespace Ui {
class Dialog_Mitarbeiter;
}

class Dialog_Mitarbeiter : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Mitarbeiter(QWidget *parent = nullptr);
    ~Dialog_Mitarbeiter();

private:
    Ui::Dialog_Mitarbeiter *ui;
};

#endif // DIALOG_MITARBEITER_H
