#include "kostenstellen.h"

kostenstellen::kostenstellen()
{

}

//-----------------public:
//-------------set:
bool kostenstellen::add(kostenstelle k)
{
    if(exist(k))
    {
        return false;
    }else
    {
        KoSt.push_back(k);
        return true;
    }
}
bool kostenstellen::del(kostenstelle k)
{
    bool retbool = false;
    for(int i=0;i<KoSt.count();i++)
    {
        if(KoSt.at(i)==k)
        {
            retbool = true;
            KoSt.erase(KoSt.begin()+i);
            break;
        }
    }
    return retbool;
}
bool kostenstellen::del(QString nr)
{
    bool retbool = false;
    for(int i=0;i<KoSt.count();i++)
    {
        if(KoSt[i].nr()==nr)
        {
            retbool = true;
            KoSt.erase(KoSt.begin()+i);
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
                    QString nr  = tzkost.zeile(1);
                    QString bez = tzkost.zeile(2);
                    kostenstelle k;
                    k.set_nr(nr);
                    k.set_bez(bez);
                    add(k);
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
        kostenstelle k;
        QString tmp;
        tmp = k.tabkopf().text().replace("\n",";");
        tmp += "\n";
        tmp += tabelle().text();
        tmp += "\n";
        tmp += "#ENDE#";
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
    bool retbool = false;
    for(int i=0;i<KoSt.count();i++)
    {
        if(KoSt[i].nr()==nr)
        {
            retbool = true;
            KoSt[i].set_bez(bez);
            break;
        }
    }
    return retbool;
}
void kostenstellen::sortieren()
{
    text_zeilenweise alt, neu;
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');
    //Vector in tz überführen:
    for(int i=0;i<KoSt.count();i++)
    {
        zeile.set_text(KoSt[i].nr());
        zeile.zeile_anhaengen(KoSt[i].bez());
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
        if(dneu >= dalt)
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
    }


    QString msg;
    msg = neu.text();
    QMessageBox mb;
    mb.setText(msg);
    mb.exec();
}
//-------------get:
text_zeilenweise kostenstellen::tabelle()
{
    text_zeilenweise tab;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(';');
    for(int i=0;i<KoSt.count();i++)
    {
        zeile.set_text(KoSt[i].nr());
        zeile.zeile_anhaengen(KoSt[i].bez());
        tab.zeile_anhaengen(zeile.text());
    }
    return tab;
}
kostenstelle kostenstellen::kost(QString nr)
{
    kostenstelle k;
    for(int i=0;i<KoSt.count();i++)
    {
        if(KoSt[i].nr()==nr)
        {
            k = KoSt.at(i);
            break;
        }
    }
    return k;
}
//-----------------private:
bool kostenstellen::exist(kostenstelle k)
{
 bool retbool = false;
 for(int i=0;i<KoSt.count();i++)
 {
     if(KoSt[i].nr()==k.nr())
     {
         retbool = true;
         break;
     }
 }
 return retbool;
}

