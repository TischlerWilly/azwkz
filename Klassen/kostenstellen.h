#ifndef KOSTENSTELLEN_H
#define KOSTENSTELLEN_H

#include <QVector>
#include "kostenstelle.h"
#include "text_zeilenweise.h"

class kostenstellen
{
public:
    kostenstellen();
    bool add(kostenstelle k);
    bool del(kostenstelle k);

    text_zeilenweise tabelle();

private:
    QVector<kostenstelle> KoSt; //Kostenstellen

    bool exist(kostenstelle k);
};

#endif // KOSTENSTELLEN_H
