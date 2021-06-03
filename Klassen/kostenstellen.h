#ifndef KOSTENSTELLEN_H
#define KOSTENSTELLEN_H

#include <QVector>
#include <QMessageBox>

#include "kostenstelle.h"
#include "text_zeilenweise.h"
#include "Klassen/prgpfade.h"

class kostenstellen
{
public:
    kostenstellen();
    bool add(kostenstelle k);
    bool del(kostenstelle k);
    bool del(QString nr);
    void initialisieren();
    void speichern();
    void clear();
    bool set_bez(QString nr, QString bez);
    void sortieren();

    text_zeilenweise tabelle();
    kostenstelle kost(QString nr);

private:
    QVector<kostenstelle> KoSt; //Kostenstellen
    prgpfade prgpf;

    bool exist(kostenstelle k);
};

#endif // KOSTENSTELLEN_H
