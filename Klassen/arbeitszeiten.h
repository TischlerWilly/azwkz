#ifndef ARBEITSZEITEN_H
#define ARBEITSZEITEN_H

#include "Klassen/tabelle_qstring.h"

class arbeitszeiten
{
public:
    arbeitszeiten();

private:
    tabelle_qstring ArbZeit;
    bool add(liste_QString z);
    bool del(liste_QString z);
    void clear();

    text_zeilenweise tabelle_tz();
    tabelle_qstring *tabelle();

};

#endif // ARBEITSZEITEN_H
