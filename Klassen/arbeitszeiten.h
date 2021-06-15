#ifndef ARBEITSZEITEN_H
#define ARBEITSZEITEN_H

#include "Klassen/tabelle_qstring.h"

class arbeitszeiten
{
public:
    arbeitszeiten();

public:
    bool add(liste_QString z);
    bool del(liste_QString z);
    void clear();

    text_zeilenweise tabelle_tz();
    tabelle_qstring *tabelle();
    tabelle_qstring tabelle(QString idscan, QDate von, QDate bis);

private:
    tabelle_qstring ArbZeit;


};

#define INDEX_ARBZEIT_IDSCAN    0
#define INDEX_ARBZEIT_TAG       1
#define INDEX_ARBZEIT_UHRZEIT   2
#define INDEX_ARBZEIT_PROJEKT   3
#define INDEX_ARBZEIT_KST       4

#endif // ARBEITSZEITEN_H
