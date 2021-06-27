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
    }else if((s.count() == 2+1+2+1+2) && (s.at(2) == ":") && (s.at(5) == ":")) //z.B.: 10:30:00
    {
        QString h, min, sekunden;
        h = text_links(s,":");
        QString trenner = ":";
        QString rest = text_rechts(s, h+trenner);
        min = text_links(rest,":");
        sekunden = text_rechts(rest, min+trenner);
        t.setHMS(h.toInt(), min.toInt(), sekunden.toInt());
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

//-----------------------------------------Operatoren:
QTime operator -(QTime t1, QTime t2)
{
    QTime ret_time;
    int minuent_h = t1.hour();
    int minuent_min = t1.minute();
    int subtrahend_h = t2.hour();
    int subtrahend_min = t2.minute();
    int dif_h = 0;
    int dif_min = 0;
    if(t1 > t2)//beide Uhrzeiten sind am selben Tag
    {
        dif_h = minuent_h - subtrahend_h;
        if(minuent_min >= subtrahend_min)
        {
            dif_min = minuent_min - subtrahend_min;
        }else
        {
            dif_min = 60 - (subtrahend_min - minuent_min);
            dif_h = dif_h - 1;
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
QTime operator +(QTime t1, QTime t2)
{
    QTime ret_time;
    int h1 = t1.hour();
    int h2 = t2.hour();
    int min1 = t1.minute();
    int min2 = t2.minute();
    int h = h1 + h2;
    int min = min1 + min2;
    if(min > 60)
    {
        h = h + 1;
        min = min - 60;
    }
    ret_time.setHMS(h,min,0);
    return ret_time;
}






