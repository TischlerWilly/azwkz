#include "kostenstellen.h"

kostenstellen::kostenstellen()
{
    liste_QString tabkopf;
    tabkopf.anhaengen("Nummer");
    tabkopf.anhaengen("Bezeichnung");
    KoSt.set_tabkopf(tabkopf);
}

//-----------------public:
//-------------set:
bool kostenstellen::add(liste_QString k)
{
    bool existiert = false;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(k.wert(INDEX_KOST_NUMMER) == KoSt.wert(i, INDEX_KOST_NUMMER))
        {
            existiert = true;
            break;
        }
    }
    if(!existiert)
    {
        KoSt.zeile_anhaengen(k);
        return false;//Es gab keinen Fehler
    }else
    {
        return  true;//Es gab einen Fehler
    }
}
bool kostenstellen::del(liste_QString k)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(k.wert(INDEX_KOST_NUMMER) == KoSt.wert(i, INDEX_KOST_NUMMER))
        {
            retbool = false;//Es gab keinen Fehler
            KoSt.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
bool kostenstellen::del(QString nr)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(nr == KoSt.wert(i, INDEX_KOST_NUMMER))
        {
            retbool = false;//es gab keinen Fehler
            KoSt.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
void kostenstellen::initialisieren()
{
    QFile file(prgpf.path_KoStFile());
    if(!file.exists())
    {//Datei erzeugen:
        speichern();
    }else
    {//Datei einlesen:
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += prgpf.path_KoStFile();
            tmp += "\n";
            tmp += "beim Lesen der Kostenstellen";
            QMessageBox::warning(new QDialog,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            KoSt.clear();
            text_zeilenweise file_tz;
            file_tz.set_text(file.readAll());
            for(uint i=2;i<=file_tz.zeilenanzahl();i++)//mit Zeile 2 beginnen weil 1.Zeile==Tabellenkopf
            {
                QString zeile = file_tz.zeile(i);
                text_zeilenweise tzkost;
                tzkost.set_trennzeichen(';');
                tzkost.set_text(zeile);
                liste_QString lqs;
                lqs.von_tz(tzkost);
                KoSt.zeile_anhaengen(lqs);
            }
        }
        file.close();
    }
}
void kostenstellen::speichern()
{
    QFile f(prgpf.path_KoStFile());
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += prgpf.path_KoStFile();
        tmp += "\n";
        tmp += "beim Speichern der Kostenstellen";
        QMessageBox::warning(new QDialog,"Fehler", tmp, QMessageBox::Ok);
    }else
    {
        QString tmp;
        tmp = KoSt.tabkopf().tz(';').text();
        tmp += "\n";
        tmp += KoSt.tabelle_tz('\n', ';').text();
        f.write(tmp.toUtf8());
    }
    f.close();
}
void kostenstellen::clear()
{
    KoSt.clear();
}
bool kostenstellen::set_bez(QString nr, QString bez)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(nr == KoSt.wert(i, INDEX_KOST_NUMMER))
        {
            retbool = false;//es gab keinen Fehler
            KoSt.set_wert(i, INDEX_KOST_BEZEICHUNG, bez);
            break;
        }
    }
    return retbool;
}
void kostenstellen::sortieren()
{
    KoSt.sortieren_double(INDEX_KOST_NUMMER);
}
//-------------get:
text_zeilenweise kostenstellen::tabelle_tz()
{
    text_zeilenweise tab;    
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        tab.zeile_anhaengen(KoSt.zeile(i).tz(';').text());
    }
    return tab;
}
tabelle_qstring *kostenstellen::tabelle()
{
    return &KoSt;
}
liste_QString kostenstellen::zeile_nr(QString nr)
{
    liste_QString lqs;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(nr == KoSt.wert(i, INDEX_KOST_NUMMER))
        {
            lqs = KoSt.zeile(i);
            break;
        }
    }
    return lqs;
}
QString kostenstellen::bez(QString nr)
{
    QString bez;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(nr == KoSt.wert(i, INDEX_KOST_NUMMER))
        {
            bez = KoSt.wert(i, INDEX_KOST_BEZEICHUNG);
            break;
        }
    }
    return bez;
}
