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

