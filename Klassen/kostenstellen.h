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
    void initialisieren();
    void speichern();
    void clear();

    text_zeilenweise tabelle();

private:
    QVector<kostenstelle> KoSt; //Kostenstellen
    prgpfade prgpf;

    bool exist(kostenstelle k);
};

#endif // KOSTENSTELLEN_H
