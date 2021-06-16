#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ToDo.h"
#include "Klassen/prgpfade.h"
#include "Klassen/arbeitszeiten.h"
#include "Dialoge/dialog_kostenstellen.h"
#include "Dialoge/dialog_mitarbeiter.h"
#include "Dialoge/dialog_azimport.h"
#include "Dialoge/dialog_tageszettel.h"

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
    void resizeEvent(QResizeEvent *event);
    void slot_kost(kostenstellen k);
    void slot_mitarb(mitarbeiter m);
    void on_actionKostenstellen_triggered();
    void on_actionMitarbeiter_triggered();

    void on_actionTageszettel_triggered();

    void on_actionImport_Uebersicht_triggered();

private:
    Ui::MainWindow *ui;
    prgpfade prgpf;
    kostenstellen KoSt;
    mitarbeiter  Mitarb;
    arbeitszeiten Arbzeit;
    Dialog_Kostenstellen Dlg_KoSt;
    Dialog_Mitarbeiter Dlg_Mitarb;
    Dialog_azimport Dlg_azimport;
    Dialog_tageszettel Dlg_tagzet;

};
#endif // MAINWINDOW_H
