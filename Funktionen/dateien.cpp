#include "Funktionen/dateien.h"

liste_QString dateien_erfassen(QDir d)
{
    liste_QString liste;
    QStringList ordnerinhalt;
    ordnerinhalt = d.entryList(QDir::Files);
    text_zeilenweise tz;
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        QString pfad;
        pfad = d.path() + QDir::separator() + name;
        liste.anhaengen(pfad);
    }
    return liste;
}

