#include "Funktionen/zeit_datum.h"

QTime text_zu_qtime(QString s)
{
    QTime t;
    if((s.count() == 2+1+2) && (s.at(2) == ":")) //z.B.: 10:30
    {
        QString h, min;
        h = text_links(s,":");
        min = text_rechts(s,":");
        t.setHMS(h.toInt(), min.toInt(), 0);
    }
    return t;
}

QDate text_zu_qdate(QString s)
{
    QDate d;
    if((s.count()==10)&&(s.at(4)==".")&&(s.at(7)=="."))//z.B.: 2021.06.14
    {
        QString jahr, monat, tag;
        jahr = text_links(s, ".");
        monat = text_mitte(s, ".",".");
        tag = text_rechts((text_rechts(s,".")),".");
        d.setDate(jahr.toInt(), monat.toInt(), tag.toInt());
    }
    return d;
}





