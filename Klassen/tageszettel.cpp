#include "tageszettel.h"

tageszettel::tageszettel(QString persnr, QString tag)
{
    liste_QString tabkopf;
    tabkopf.anhaengen("Projekt");
    tabkopf.anhaengen("KST");
    tabkopf.anhaengen("Dauer");
    tabkopf.anhaengen("PersNr");
    tabkopf.anhaengen("Tag");
    TagZet.set_tabkopf(tabkopf);
    KoSt = NULL;
    PersNr = persnr;
    Tag = tag;
}
void tageszettel::set_KoSt(kostenstellen *kst)
{
    KoSt = kst;
}

void tageszettel::add(QString projekt, QString kst, QTime dauer)
{
    if(KoSt != NULL)
    {
        if(KoSt->gk(kst))//kst ist Gemeinkosten
        {
            projekt = "GK";
            QString jahr;
            jahr = int_to_qstring(QDate::currentDate().year());
            jahr = text_rechts(jahr, "20");
            projekt += jahr;
        }
        bool bekannt = false;
        for(int i=0;i<TagZet.anz_zeilen();i++)
        {
            if(TagZet.wert(i, INDEX_TAGZET_PROJEKT) == projekt)
            {
                if(TagZet.wert(i, INDEX_TAGZET_KST) == kst)
                {
                    bekannt = true;
                    QString dauer_vorher = TagZet.wert(i, INDEX_TAGZET_DAUER);
                    QTime vorwert = text_zu_qtime(dauer_vorher);
                    QTime neuedauer = vorwert + dauer;
                    TagZet.set_wert(i, INDEX_TAGZET_DAUER, neuedauer.toString());
                    break;
                }
            }
        }
        if(bekannt == false)
        {
            liste_QString lqs;
            lqs.anhaengen(projekt);
            lqs.anhaengen(kst);
            lqs.anhaengen(dauer.toString());
            lqs.anhaengen(PersNr);
            lqs.anhaengen(Tag);
            TagZet.zeile_anhaengen(lqs);
        }
    }else
    {
        QMessageBox mb;
        mb.setText("Fehler in funktion arbeitszeiten::tagzet(..)\n Zeiger für KoSt wurde nicht übergeben.");
    }
}

tabelle_qstring tageszettel::tabelle()
{
    return TagZet;
}
tabelle_qstring tageszettel::tabelle_ohne_pausen()
{
    tabelle_qstring tab;
    tab.set_tabkopf(TagZet.tabkopf());
    for(int i=0;i<TagZet.anz_zeilen();i++)
    {
        QString kst = TagZet.wert(i, INDEX_TAGZET_KST);
        if(kst != "000")
        {
            tab.zeile_anhaengen(TagZet.zeile(i));
        }
    }
    return tab;
}
