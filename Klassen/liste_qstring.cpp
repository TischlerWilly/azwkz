#include "liste_qstring.h"

liste_QString::liste_QString()
{

}

//------------------set_xy:
void liste_QString::von_tz(text_zeilenweise tz)
{
    clear();
    for(uint i=1;i<=tz.zeilenanzahl();i++)
    {
        Vs.push_back(tz.zeile(i));
    }
}
void liste_QString::vorwecksetzen(QString wert)
{
    Vs.push_front(wert);
}
void liste_QString::anhaengen(QString wert)
{
    Vs.push_back(wert);
}
void liste_QString::einfuegen(int index, QString wert)
{
    //Bei index 0 wird wert vorweckgesetzt
    //Bei index size() wird wert angehängt
    //bei z.B. index 2 ist nach dem Einfügen wert an 3. Stelle
    //Vs[0] == irgendwas
    //Vs[1] == irgendwas
    //Vs[2] == wert
    //Vs[3] == irgendwas war ehemals Vs[2]
    Vs.insert(index, wert);
}
void liste_QString::einfuegen(int index, text_zeilenweise tz)
{
    if(index == 0)
    {
        for(uint i=tz.zeilenanzahl();i>=1;i--)
        {
            Vs.push_front(tz.zeile(i));
        }
    }else if(index == Vs.size())
    {
        for(uint i=1;i<=tz.zeilenanzahl();i++)
        {
            Vs.push_back(tz.zeile(i));
        }
    }else
    {
        for(uint i=1;i<=tz.zeilenanzahl();i++)
        {
            Vs.insert(index+i-1, tz.zeile(i));
        }
    }
}
void liste_QString::ersaetzen(int index, QString wert)
{
    if((index >= 0) && (index < Vs.size()))
    {
        Vs[index] = wert;
    }
}
void liste_QString::loeschen(int index)
{
    Vs.remove(index);
}
void liste_QString::loeschen(int index, int anz_werte)
{
    Vs.remove(index, anz_werte);
}

//------------------get_xy:
text_zeilenweise liste_QString::tz(char trennzeichen)
{
    QString ret;
    for(int i=0;i<Vs.count();i++)
    {
        if(!ret.isEmpty())
        {
            ret += trennzeichen;
        }
        ret += Vs.at(i);
    }
    text_zeilenweise tz;
    tz.set_text(ret);
    return tz;
}
QStringList liste_QString::qstringlist()
{
    QStringList ret;
    for(int i=0;i<Vs.count();i++)
    {
        ret.append(Vs.at(i));
    }
    return ret;
}
QString liste_QString::wert(int index)
{
    return Vs.at(index);
}
text_zeilenweise liste_QString::werte_tz(int index, int anz_werte)
{
    text_zeilenweise tz;
    for(int i=index;i<index+anz_werte;i++)
    {
        int akt_index = i+anz_werte-1;
        tz.zeile_anhaengen(Vs.at(akt_index));
    }
    return tz;
}
liste_QString liste_QString::werte_liste(int index, int anz_werte)
{
    liste_QString liste;
    for(int i=index;i<index+anz_werte;i++)
    {
        int akt_index = i+anz_werte-1;
        liste.anhaengen(Vs.at(akt_index));
    }
    return liste;
}
int liste_QString::count()
{
    return Vs.count();
}

//------------------Manipulationen:
void liste_QString::clear()
{
    Vs.clear();
}





