#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ToDo.h"
#include "Klassen/prgpfade.h"
#include "Dialoge/dialog_kostenstellen.h"
#include "Dialoge/dialog_mitarbeiter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_kost(kostenstellen k);
    void slot_mitarb(mitarbeiter m);
    void on_actionKostenstellen_triggered();
    void on_actionMitarbeiter_triggered();

private:
    Ui::MainWindow *ui;
    prgpfade prgpf;
    kostenstellen KoSt;
    mitarbeiter  Mitarb;
    Dialog_Kostenstellen Dlg_KoSt;
    Dialog_Mitarbeiter Dlg_Mitarb;
};
#endif // MAINWINDOW_H
