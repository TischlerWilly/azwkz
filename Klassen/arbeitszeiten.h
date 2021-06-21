#ifndef ARBEITSZEITEN_H
#define ARBEITSZEITEN_H

#include <QMessageBox>

#include "Klassen/tabelle_qstring.h"
#include "Klassen/prgpfade.h"
#include "Funktionen/dateien.h"

class arbeitszeiten
{
public:
    arbeitszeiten();

public:
    bool add(liste_QString z);
    bool del(liste_QString z);
    void clear();
    void import();

    text_zeilenweise tabelle_tz();
    tabelle_qstring *tabelle();
    tabelle_qstring tabelle(QString idscan, QDate von, QDate bis);
    tabelle_qstring tagzet(QString idscan, QDate tag);

private:
    tabelle_qstring ArbZeit;


};

#define INDEX_ARBZEIT_IDSCAN    0
#define INDEX_ARBZEIT_TAG       1
#define INDEX_ARBZEIT_UHRZEIT   2
#define INDEX_ARBZEIT_PROJEKT   3
#define INDEX_ARBZEIT_KST       4

#endif // ARBEITSZEITEN_H
