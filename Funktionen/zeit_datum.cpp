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
QTime minus(QTime minuent, QTime subtrahend)
{
    QTime ret_time;
    int minuent_h = minuent.hour();
    int minuent_min = minuent.minute();
    int subtrahend_h = subtrahend.hour();
    int subtrahend_min = subtrahend.minute();
    int dif_h = 0;
    int dif_min = 0;
    if(minuent > subtrahend)//beide Uhrzeiten sind am selben Tag
    {
        dif_h = minuent_h - subtrahend_h;
        if(minuent_min >= subtrahend_min)
        {
            dif_min = minuent_min - subtrahend_min;
        }else
        {
            dif_min = 60 - (subtrahend_min - minuent_min);
        }
    }else//beide Uhrzeiten sind nicht am selben Tag
    {
        //noch programmieren
        //...
        //...
        //...
        //...
    }
    ret_time.setHMS(dif_h, dif_min, 0);
    return ret_time;
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





