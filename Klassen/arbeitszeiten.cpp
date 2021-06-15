#include "arbeitszeiten.h"

arbeitszeiten::arbeitszeiten()
{
    liste_QString tabkopf;
    tabkopf.anhaengen("id-scanner");
    tabkopf.anhaengen("Tag");
    tabkopf.anhaengen("Uhrzeit");
    tabkopf.anhaengen("Projekt");
    tabkopf.anhaengen("Kostenstelle");
    ArbZeit.set_tabkopf(tabkopf);
}

//-----------------public:
//-------------set:
bool arbeitszeiten::add(liste_QString z)
{
    bool existiert = false;
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        if(z.tz('\n').text() == ArbZeit.zeile(i).tz('\n').text())
        {
            existiert = true;
            break;
        }
    }
    if(!existiert)
    {
        ArbZeit.zeile_anhaengen(z);
        return false;//Es gab keinen Fehler
    }else
    {
        return  true;//Es gab einen Fehler
    }
}
bool arbeitszeiten::del(liste_QString z)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        if(z.tz('\n').text() == ArbZeit.zeile(i).tz('\n').text())
        {
            retbool = false;//Es gab keinen Fehler
            ArbZeit.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
void arbeitszeiten::clear()
{
    ArbZeit.clear();
}

//-------------get:
text_zeilenweise arbeitszeiten::tabelle_tz()
{
    text_zeilenweise tab;
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        tab.zeile_anhaengen(ArbZeit.zeile(i).tz(';').text());
    }
    return tab;
}
tabelle_qstring *arbeitszeiten::tabelle()
{
    return &ArbZeit;
}
tabelle_qstring arbeitszeiten::tabelle(QString idscan, QDate von, QDate bis)
{
    tabelle_qstring tab;
    tab.set_tabkopf(ArbZeit.tabkopf());
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        if(idscan.isEmpty())
        {
            QDate datum_zeile;
            datum_zeile = text_zu_qdate(ArbZeit.wert(i,INDEX_ARBZEIT_TAG));
            if((von <= datum_zeile) && (datum_zeile <= bis))
            {
                tab.zeile_anhaengen(ArbZeit.zeile(i));
            }
        }else
        {
            if(ArbZeit.wert(i, INDEX_ARBZEIT_IDSCAN) == idscan)
            {
                QDate datum_zeile;
                datum_zeile = text_zu_qdate(ArbZeit.wert(i,INDEX_ARBZEIT_TAG));
                if((von <= datum_zeile) && (datum_zeile <= bis))
                {
                    tab.zeile_anhaengen(ArbZeit.zeile(i));
                }
            }
        }
    }
    return tab;
}




