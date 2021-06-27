#ifndef TAGESZETTEL_H
#define TAGESZETTEL_H

#include <QTime>
#include "Klassen/tabelle_qstring.h"
#include "Klassen/kostenstellen.h"

class tageszettel
{
public:
    tageszettel(QString persnr, QString tag);
    void set_KoSt(kostenstellen *kst);
    void add(QString projekt, QString kst, QTime dauer);

    tabelle_qstring tabelle();
    tabelle_qstring tabelle_ohne_pausen();

private:
    tabelle_qstring TagZet;
    kostenstellen *KoSt;
    QString PersNr;
    QString Tag;
};

#define INDEX_TAGZET_PROJEKT    0
#define INDEX_TAGZET_KST        1
#define INDEX_TAGZET_DAUER      2

#endif // TAGESZETTEL_H
