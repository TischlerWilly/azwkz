#ifndef KOSTENSTELLE_H
#define KOSTENSTELLE_H

#include <QString>
#include "text_zeilenweise.h"

class kostenstelle
{
public:
    kostenstelle();
    void set_nr(QString nummer);
    void set_bez(QString bez);

    QString nr();
    QString bez();
    text_zeilenweise tabkopf();


private:
    QString Nummer;
    QString Bezeichnung;
};

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(kostenstelle k1, kostenstelle k2);
bool operator !=(kostenstelle k1, kostenstelle k2);

#endif // KOSTENSTELLE_H
