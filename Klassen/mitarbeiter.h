#ifndef MITARBEITER_H
#define MITARBEITER_H

#include <QMessageBox>

#include "Klassen/prgpfade.h"
#include "Klassen/tabelle_qstring.h"


class mitarbeiter
{
public:
    mitarbeiter();
    bool add(liste_QString m);
    bool del(liste_QString m);
    bool del(QString nr);
    void initialisieren();
    void speichern();
    void clear();
    bool set_vorname(QString nr, QString nam);
    bool set_nachname(QString nr, QString nam);
    int set_idscanner(QString nr, QString id);
    void sortieren();

    text_zeilenweise tabelle_tz();
    tabelle_qstring *tabelle();
    liste_QString zeile_nr(QString nr);
    liste_QString zeile_idscan(QString id);


private:
    tabelle_qstring Mitarb;
    prgpfade prgpf;

};

#define INDEX_MITARB_NUMMER         0
#define INDEX_MITARB_VORNAME        1
#define INDEX_MITARB_NACHNAME       2
#define INDEX_MITARB_IDSCANNER      3

#endif // MITARBEITER_H
