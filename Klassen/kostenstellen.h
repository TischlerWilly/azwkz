#ifndef KOSTENSTELLEN_H
#define KOSTENSTELLEN_H

#include <QMessageBox>

#include "Klassen/prgpfade.h"
#include "Klassen/tabelle_qstring.h"

class kostenstellen
{
public:
    kostenstellen();
    bool add(liste_QString k);
    bool del(liste_QString k);
    bool del(QString nr);
    void initialisieren();
    void speichern();
    void clear();
    bool set_bez(QString nr, QString bez);
    void sortieren();

    text_zeilenweise tabelle_tz();
    tabelle_qstring *tabelle();
    liste_QString zeile_nr(QString nr);

private:
    tabelle_qstring KoSt;
    prgpfade prgpf;

};

#define INDEX_KOST_NUMMER        0
#define INDEX_KOST_BEZEICHUNG    1

#endif // KOSTENSTELLEN_H
