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
void arbeitszeiten::import()
{
    prgpfade pf;
    QDir idir = pf.dir_import_az();
    liste_QString dateien = dateien_erfassen(idir);
    for(int i=0;i<dateien.count();i++)//Datei für Datei einlesen
    {
        QFile f(dateien.qstringlist().at(i));
        text_zeilenweise tz;
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString msg;
            msg = "Fehler beim zugriff auf die Datei \"";
            msg += dateien.qstringlist().at(i);
            msg += "\"!";
            QMessageBox::warning(new QDialog,"Fehler",msg,QMessageBox::Ok);
        }else
        {
            tz.set_text(QString::fromLatin1(f.readAll()));
        }
        for(uint ii=2;ii<tz.zeilenanzahl();ii++)//Zeile für Zeile speichern
        {//Erst in 2. Zeile beginnen weil 1. Zeile Tabellenkpf ist
            text_zeilenweise zeile_tz;
            zeile_tz.set_trennzeichen('\t');
            zeile_tz.set_text(tz.zeile(ii));
            liste_QString zeile;
            QString idscan, tag, zeit, proj, kst;
            idscan = zeile_tz.zeile(4);
            tag = zeile_tz.zeile(5);
            zeit = zeile_tz.zeile(3);
            proj = zeile_tz.zeile(1);
            kst = zeile_tz.zeile(2);
            zeile.anhaengen(idscan);
            zeile.anhaengen(tag);
            zeile.anhaengen(text_links(zeit,"Uhr"));
            zeile.anhaengen(proj);
            zeile.anhaengen(kst);
            add(zeile);
        }
    }
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




