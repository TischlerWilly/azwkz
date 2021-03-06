#include "tabelle_qstring.h"

tabelle_qstring::tabelle_qstring()
{
    clear();
    tabkopf().clear();
}

//----------------set_xy:
void tabelle_qstring::set_tabkopf(liste_QString kopf)
{
    clear();
    Tabkopf = kopf;
}
bool tabelle_qstring::set_wert(int index_zeile, int indes_spalte, QString wert)
{
    if(index_zeile < anz_zeilen() && indes_spalte < anz_spalten())
    {
        Liqs[index_zeile].ersaetzen(indes_spalte, wert);
        return false;//Es gab keinen Fehler
    }else
    {
        return true;//Es gab einen Fehler
    }
}
bool tabelle_qstring::zeile_anhaengen(liste_QString zeile)
{
    if(zeile.count() != anz_spalten())
    {        
        return true;//Es gab einen Fehler
    }else
    {
        Liqs.push_back(zeile);
        return false;//Es geb keinen Fehler
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
text_zeilenweise tabelle_qstring::tabelle_tz(char trennz_zeile, char trennz_spalte)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(trennz_zeile);
    for(int i=0;i<anz_zeilen();i++)
    {
        tz.zeile_anhaengen(zeile(i).tz(trennz_spalte).text());
    }
    return tz;;
}
liste_QString tabelle_qstring::zeile(int index)
{
    if((index >= 0) && (index < Liqs.count()))
    {
        return Liqs.at(index);
    }else
    {
        liste_QString tmp;
        return tmp;
    }

}
liste_QString tabelle_qstring::tabkopf()
{
    return Tabkopf;
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
}
bool tabelle_qstring::zeile_entfernen(int index)
{
    if(index < Liqs.count())
    {
        Liqs.remove(index);
        return false;//Es gab keinen Fehler
    }else
    {
        return true;//Es gab einen Fehler
    }
}
void tabelle_qstring::sortieren_double(int index_sortierspalte)
{
    //Diese Funktion sorteiert die tabelle basierend auf den Werten in Spalte
    //"index_sortierspalte" um
    //verglichen werden die in double umgewandelten Werte    

    if(Liqs.count()>1)
    {
        QVector<liste_QString> liqs_neu;
        //1. Zeile einfach verschieben:
        liqs_neu.push_back(Liqs.at(0));
        Liqs.remove(0);
        //2. Zeile davor oder dannach:
        double dalt = Liqs[0].wert(index_sortierspalte).toDouble();
        double dneu = liqs_neu[0].wert(index_sortierspalte).toDouble();
        if(dalt >= dneu)
        {
            liqs_neu.push_back(Liqs.at(0));
        }else
        {
            liqs_neu.push_front(Liqs.at(0));
        }
        Liqs.remove(0);
        //restliche werte einsortieren:
        while(Liqs.count()>=1)
        {
            dalt = Liqs[0].wert(index_sortierspalte).toDouble();
            dneu = liqs_neu[0].wert(index_sortierspalte).toDouble();
            if(dalt <= dneu)//Wenn alt <= erster Wert von neu
            {
                liqs_neu.push_front(Liqs.at(0));
                Liqs.remove(0);
            }else
            {
                dneu = liqs_neu[liqs_neu.count()-1].wert(index_sortierspalte).toDouble();
                if(dalt >= dneu)//Wenn alt >= letzter Wert von neu
                {
                    liqs_neu.push_back(Liqs.at(0));
                    Liqs.remove(0);
                }else//der Wert geh??rt irgendwo in die Mitte
                {
                    for(int i=0;i<liqs_neu.count()-1;i++)
                    {
                        double daktzei;//Wert der aktuellen Zeile
                        daktzei = liqs_neu[i].wert(index_sortierspalte).toDouble();
                        double dfolzei;//Wert der n??chsten Zeile
                        dfolzei = liqs_neu[i+1].wert(index_sortierspalte).toDouble();
                        if((dalt >= daktzei) && (dalt <=dfolzei))
                        {
                            liqs_neu.insert(i+1, Liqs.at(0));
                            Liqs.remove(0);
                            break;
                        }
                    }
                }
            }
        }
        //Werte zur??ckspeichern:
        Liqs = liqs_neu;
    }
}


