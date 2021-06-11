#include "mitarbeiter.h"

mitarbeiter::mitarbeiter()
{
    liste_QString tabkopf;
    tabkopf.anhaengen("Pers.Nr.");
    tabkopf.anhaengen("Vorname");
    tabkopf.anhaengen("Nachname");
    tabkopf.anhaengen("ID-Scanner");
    Mitarb.set_tabkopf(tabkopf);
}
//-----------------public:
//-------------set:
bool mitarbeiter::add(liste_QString m)
{
    bool existiert = false;
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        if(m.wert(INDEX_MITARB_NUMMER) == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            existiert = true;
            break;
        }
    }
    if(!existiert)
    {
        Mitarb.zeile_anhaengen(m);
        return false;//Es gab keinen Fehler
    }else
    {
        return  true;//Es gab einen Fehler
    }
}
bool mitarbeiter::del(liste_QString m)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        if(m.wert(INDEX_MITARB_NUMMER) == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            retbool = false;//Es gab keinen Fehler
            Mitarb.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
bool mitarbeiter::del(QString nr)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        if(nr == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            retbool = false;//es gab keinen Fehler
            Mitarb.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
void mitarbeiter::initialisieren()
{
    QFile file(prgpf.path_MitarbFile());
    if(!file.exists())
    {//Datei erzeugen:
        speichern();
    }else
    {//Datei einlesen:
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += prgpf.path_MitarbFile();
            tmp += "\n";
            tmp += "beim Lesen der Mitarbeiter";
            QMessageBox::warning(new QDialog,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            Mitarb.clear();
            text_zeilenweise file_tz;
            file_tz.set_text(file.readAll());
            for(uint i=2;i<=file_tz.zeilenanzahl();i++)//mit Zeile 2 beginnen weil 1.Zeile==Tabellenkopf
            {
                QString zeile = file_tz.zeile(i);
                text_zeilenweise tzmitarb;
                tzmitarb.set_trennzeichen(';');
                tzmitarb.set_text(zeile);
                liste_QString lqs;
                lqs.von_tz(tzmitarb);
                Mitarb.zeile_anhaengen(lqs);
            }
        }
        file.close();
    }
}
void mitarbeiter::speichern()
{
    QFile f(prgpf.path_MitarbFile());
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += prgpf.path_MitarbFile();
        tmp += "\n";
        tmp += "beim Speichern der Mitarbeiter";
        QMessageBox::warning(new QDialog,"Fehler", tmp, QMessageBox::Ok);
    }else
    {
        QString tmp;
        tmp = Mitarb.tabkopf().tz(';').text();
        tmp += "\n";
        tmp += Mitarb.tabelle_tz('\n', ';').text();
        f.write(tmp.toUtf8());
    }
    f.close();
}
void mitarbeiter::clear()
{
    Mitarb.clear();
}
bool mitarbeiter::set_vorname(QString nr, QString nam)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        if(nr == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            retbool = false;//es gab keinen Fehler
            Mitarb.set_wert(i, INDEX_MITARB_VORNAME, nam);
            break;
        }
    }
    return retbool;
}
bool mitarbeiter::set_nachname(QString nr, QString nam)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        if(nr == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            retbool = false;//es gab keinen Fehler
            Mitarb.set_wert(i, INDEX_MITARB_NACHNAME, nam);
            break;
        }
    }
    return retbool;
}
int mitarbeiter::set_idscanner(QString nr, QString id)
{
    //Returnwerte:
    //0:es gab keinen Fehler
    //1: Mitarbeiter mir Personalnummer nr gibt es nicht
    //2: Scanner-ID ist bereits vergeben
    bool mitarb_vorhanden = false;
    for(int i=0;i<Mitarb.anz_zeilen();i++)//Prüfen ob ein Mitarbeiter mit dieser Personalnummer existiert
    {
        if(nr == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            mitarb_vorhanden = true;
            for(int ii=0;ii<Mitarb.anz_zeilen();ii++)//Prüfen ob die Scanner-id bereits vergeben ist
            {
                if(ii != i)
                {                    
                    if(!id.isEmpty() && id == Mitarb.wert(ii, INDEX_MITARB_IDSCANNER))
                    {
                        return 2;//Scanner-ID ist bereits vergeben
                    }
                }
            }
            Mitarb.set_wert(i, INDEX_MITARB_IDSCANNER, id);
            return 0;//es gab keinen Fehler
        }       
    }    
    if(mitarb_vorhanden == false)
    {
        return 1;//Mitarbeiter mir Personalnummer nr gibt es nicht
    }
    return 0;
}
void mitarbeiter::sortieren()
{
    Mitarb.sortieren_double(INDEX_MITARB_NUMMER);
}
//-------------get:
text_zeilenweise mitarbeiter::tabelle_tz()
{
    text_zeilenweise tab;
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        tab.zeile_anhaengen(Mitarb.zeile(i).tz(';').text());
    }
    return tab;
}
tabelle_qstring *mitarbeiter::tabelle()
{
    return &Mitarb;
}
liste_QString mitarbeiter::zeile_nr(QString nr)
{
    liste_QString lqs;
    for(int i=0;i<Mitarb.anz_zeilen();i++)
    {
        if(nr == Mitarb.wert(i, INDEX_MITARB_NUMMER))
        {
            lqs = Mitarb.zeile(i);
            break;
        }
    }
    return lqs;
}









