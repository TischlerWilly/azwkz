#ifndef TABELLE_QSTRING_H
#define TABELLE_QSTRING_H

#include <QMessageBox>
#include <QDate>
#include <QTime>

#include "liste_qstring.h"
#include "Funktionen/umwandeln.h"
#include "Funktionen/text.h"
#include "Funktionen/zeit_datum.h"

class tabelle_qstring
{
public:
    tabelle_qstring();
    //set_xy:
    void set_tabkopf(liste_QString kopf);
    bool set_wert(int index_zeile, int indes_spalte ,QString wert);
    bool zeile_anhaengen(liste_QString zeile);

    //get_xy:
    int anz_spalten();
    int anz_zeilen();
    text_zeilenweise tabelle_tz(char trennz_zeile, char trennz_spalte);
    liste_QString zeile(int index);
    liste_QString tabkopf();
    QString wert(int zeile, int spalte);

    //Manipulationen:
    void clear();
    bool zeile_entfernen(int index);
    void sortieren_double(int index_sortierspalte);
    void sortieren_datum(int index_sortierspalte);
    void sortieren_zeit(int index_sortierspalte);

private:
    liste_QString Tabkopf;
    QVector<liste_QString> Liqs;
};

#endif // TABELLE_QSTRING_H
