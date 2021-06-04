#ifndef KOSTENSTELLEN_H
#define KOSTENSTELLEN_H

#include <QVector>
#include <QMessageBox>

#include "kostenstelle.h"
#include "text_zeilenweise.h"
#include "Klassen/prgpfade.h"
#include "Klassen/tabelle_qstring.h"

class kostenstellen
{
public:
    kostenstellen();
    bool add(kostenstelle k);//später entfernen
    bool add(liste_QString k);
    bool del(kostenstelle k);//später entfernen
    bool del(liste_QString k);
    bool del(QString nr);
    void initialisieren();
    void speichern();
    void clear();
    bool set_bez(QString nr, QString bez);
    void sortieren();

    text_zeilenweise tabelle_tz();
    kostenstelle kost(QString nr);

private:
    QVector<kostenstelle> KoSt_; //Kostenstellen
    tabelle_qstring KoSt;

    prgpfade prgpf;

    bool exist(kostenstelle k);
};

#define INDEX_NUMMER        0
#define INDEX_BEZEICHUNG    1

#endif // KOSTENSTELLEN_H
