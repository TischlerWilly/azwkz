#ifndef TABELLE_QSTRING_H
#define TABELLE_QSTRING_H

#include "liste_qstring.h"

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
    liste_QString zeile(uint index);
    QString wert(int zeile, int spalte);

    //Manipulationen:
    void clear();
    bool zeile_entfernen(int index);

private:
    liste_QString Tabkopf;
    QVector<liste_QString> Liqs;
};

#endif // TABELLE_QSTRING_H
