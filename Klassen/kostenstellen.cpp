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
bool kostenstellen::add(kostenstelle k)//später entfernen
{
    if(exist(k))
    {
        return false;
    }else
    {
        KoSt_.push_back(k);
        return true;
    }
}
bool kostenstellen::add(liste_QString k)
{
    bool existiert = false;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(k.wert(INDEX_NUMMER) == KoSt.wert(i, INDEX_NUMMER))
        {
            existiert = true;
            break;
        }
    }
    if(!existiert)
    {
        KoSt.zeile_anhaengen(k);
        return true;
    }else
    {
        return  false;
    }
}
bool kostenstellen::del(kostenstelle k)//später entfernen
{
    bool retbool = false;
    for(int i=0;i<KoSt_.count();i++)
    {
        if(KoSt_.at(i)==k)
        {
            retbool = true;
            KoSt_.erase(KoSt_.begin()+i);
            break;
        }
    }
    return retbool;
}
bool kostenstellen::del(liste_QString k)
{
    bool retbool = false;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(k.wert(INDEX_NUMMER) == KoSt.wert(i, INDEX_NUMMER))
        {
            retbool = true;
            KoSt.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
bool kostenstellen::del(QString nr)
{
    bool retbool = false;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(nr == KoSt.wert(i, INDEX_NUMMER))
        {
            retbool = true;
            KoSt.zeile_entfernen(i);
            break;
        }
    }
    //----------------------------------------------------------später entfernen:
    for(int i=0;i<KoSt_.count();i++)
    {
        if(KoSt_[i].nr()==nr)
        {
            retbool = true;
            KoSt_.erase(KoSt_.begin()+i);
            break;
        }
    }
    //-----------------------------------------------------------------
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
            text_zeilenweise tz;
            tz.set_text(file.readAll());
            for(uint i=2;i<=tz.zeilenanzahl();i++)//mit Zeile 2 beginnen weil 1.Zeile==Tabellenkopf
            {
                QString zeile = tz.zeile(i);
                if(zeile == "#ENDE#")
                {
                    break;
                }else
                {
                    text_zeilenweise tzkost;
                    tzkost.set_trennzeichen(';');
                    tzkost.set_text(zeile);
                    liste_QString lqs;
                    lqs.von_tz(tzkost);
                    KoSt.zeile_anhaengen(lqs);
                }
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
        /*
        kostenstelle k;
        QString tmp;
        tmp = k.tabkopf().text().replace("\n",";");
        tmp += "\n";
        tmp += tabelle_tz().text();
        tmp += "\n";
        tmp += "#ENDE#";
        */
        QString tmp;
        tmp = KoSt.tabkopf().tz(';').text();
        f.write(tmp.toUtf8());
    }
    f.close();
}
void kostenstellen::clear()
{
    KoSt.clear();
    KoSt_.clear();//später entfernen
}
bool kostenstellen::set_bez(QString nr, QString bez)
{
    bool retbool = false;
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        if(nr == KoSt.wert(i, INDEX_NUMMER))
        {
            retbool = true;
            KoSt.set_wert(i, INDEX_BEZEICHUNG, bez);
            break;
        }
    }
    //----------------------------------------------------------später entfernen:
    for(int i=0;i<KoSt_.count();i++)
    {
        if(KoSt_[i].nr()==nr)
        {
            retbool = true;
            KoSt_[i].set_bez(bez);
            break;
        }
    }
    //----------------------------------------------------------
    return retbool;
}
void kostenstellen::sortieren()//später entfernen
{
    text_zeilenweise alt, neu;
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');
    //Vector in tz überführen:
    for(int i=0;i<KoSt_.count();i++)
    {
        zeile.set_text(KoSt_[i].nr());
        zeile.zeile_anhaengen(KoSt_[i].bez());
        alt.zeile_anhaengen(zeile.text());
    }
    //tz sortieren(double vergleichen):
    const int posverglwert = 1;//Position des Vergleichswertes
    char tren = '\t';//Trennzeichen Spalten
    if(alt.zeilenanzahl()>1)
    {
        //1. Zeile einfach verschieben:
        neu.set_text(alt.zeile(1));
        alt.zeile_loeschen(1);
        //2. Zeile davor oder dannach:
        text_zeilenweise zeile;
        zeile.set_trennzeichen(tren);
        zeile.set_text(alt.zeile(1));
        double dalt = zeile.zeile(posverglwert).toDouble();
        zeile.set_text(neu.zeile(1));
        double dneu = zeile.zeile(posverglwert).toDouble();
        if(dalt >= dneu)
        {
            neu.zeile_anhaengen(alt.zeile(1));
        }else
        {
            neu.zeile_vorwegsetzen(alt.zeile(1));
        }
        alt.zeile_loeschen(1);
        //restliche werte einsortieren
        while(alt.zeilenanzahl()>=1)
        {
            zeile.set_text(alt.zeile(1));
            dalt = zeile.zeile(posverglwert).toDouble();
            zeile.set_text(neu.zeile(1));
            dneu = zeile.zeile(posverglwert).toDouble();
            if(dalt <= dneu)//Wenn alt <= erster Wert von neu
            {
                neu.zeile_vorwegsetzen(alt.zeile(1));
                alt.zeile_loeschen(1);
            }else
            {
                zeile.set_text(neu.zeile(neu.zeilenanzahl()));
                dneu = zeile.zeile(posverglwert).toDouble();
                if(dalt >= dneu)//Wenn alt >= letzter Wert von neu
                {
                    neu.zeile_anhaengen(alt.zeile(1));
                    alt.zeile_loeschen(1);
                }else//der Wert gehört irgendwo in die Mitte
                {
                    for(uint i=1;i<neu.zeilenanzahl()-1;i++)
                    {
                        double daktzei;//Wert der aktuellen Zeile
                        zeile.set_text(neu.zeile(i));
                        daktzei = zeile.zeile(posverglwert).toDouble();
                        double dfolzei;//Wert der nächsten Zeile
                        zeile.set_text(neu.zeile(i+1));
                        dfolzei = zeile.zeile(posverglwert).toDouble();
                        if((dalt >= daktzei) && (dalt <=dfolzei))
                        {
                            neu.zeile_einfuegen(i, alt.zeile(1));
                            alt.zeile_loeschen(1);
                            break;
                        }
                    }
                }
            }
        }
        QMessageBox mb;
        mb.setText(neu.text());
        mb.exec();
    }
}
//-------------get:
text_zeilenweise kostenstellen::tabelle_tz()
{
    text_zeilenweise tab;    
    for(int i=0;i<KoSt.anz_zeilen();i++)
    {
        tab.zeile_anhaengen(KoSt.zeile(i).tz(';').text());
    }
    //----------------------------------------------------------später entfernen:
    tab.clear();
    text_zeilenweise zeile;
    zeile.set_trennzeichen(';');
    for(int i=0;i<KoSt_.count();i++)
    {
        zeile.set_text(KoSt_[i].nr());
        zeile.zeile_anhaengen(KoSt_[i].bez());
        tab.zeile_anhaengen(zeile.text());
    }
    //----------------------------------------------------------
    return tab;
}
tabelle_qstring kostenstellen::tabelle()
{
    return KoSt;
}
kostenstelle kostenstellen::kost(QString nr)//später entfernen
{
    kostenstelle k;
    for(int i=0;i<KoSt_.count();i++)
    {
        if(KoSt_[i].nr()==nr)
        {
            k = KoSt_.at(i);
            break;
        }
    }
    return k;
}
//-----------------private:
bool kostenstellen::exist(kostenstelle k)//später entfernen
{
 bool retbool = false;
 for(int i=0;i<KoSt_.count();i++)
 {
     if(KoSt_[i].nr()==k.nr())
     {
         retbool = true;
         break;
     }
 }
 return retbool;
}

