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
    bool set_gk(QString nr, bool ist_gk);
    void sortieren();

    text_zeilenweise tabelle_tz();
    tabelle_qstring *tabelle();
    liste_QString zeile_nr(QString nr);
    QString bez(QString nr);
    bool gk(QString nr);

private:
    tabelle_qstring KoSt;
    prgpfade prgpf;

};

#define INDEX_KOST_NUMMER        0 //"000" bis "999"
#define INDEX_KOST_BEZEICHUNG    1 //frei wählbar
#define INDEX_KOST_GK            2 // "1" oder "0"
#define INDEX_KOST_PERSNR        3
#define INDEX_KOST_TAG           4

#endif // KOSTENSTELLEN_H
