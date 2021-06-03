#include "tabelle_qstring.h"

tabelle_qstring::tabelle_qstring()
{
    clear();
}

//----------------set_xy:
void tabelle_qstring::set_tabkopf(liste_QString kopf)
{
    clear();
    Tabkopf = kopf;
}
bool tabelle_qstring::zeile_anhaengen(liste_QString zeile)
{
    if(zeile.count() != anz_spalten())
    {
        return false;
    }else
    {
        Liqs.push_back(zeile);
        return true;
    }
}


//----------------get_xy:
int tabelle_qstring::anz_spalten()
{
    return Tabkopf.count();
}
int tabelle_qstring::anz_zeilen()
{
    return Liqs.count();
}
liste_QString tabelle_qstring::zeile(uint index)
{
    return Liqs.at(index);
}
QString tabelle_qstring::wert(int zeile, int spalte)
{
    QString ret;
    if((zeile < anz_zeilen()) && (spalte < anz_spalten()))
    {
        ret = Liqs[zeile].wert(spalte);
    }
    return ret;
}

//----------------Manipulationen:
void tabelle_qstring::clear()
{
    Liqs.clear();
    Tabkopf.clear();
}



