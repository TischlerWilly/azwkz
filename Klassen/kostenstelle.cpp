#include "kostenstelle.h"

kostenstelle::kostenstelle()
{

}

//-------------set:
void kostenstelle::set_nr(QString nummer)
{
    Nummer = nummer;
}
void kostenstelle::set_bez(QString bez)
{
    Bezeichnung = bez;
}

//-------------get:
QString kostenstelle::nr()
{
    return Nummer;
}
QString kostenstelle::bez()
{
    return Bezeichnung;
}
text_zeilenweise kostenstelle::tabkopf()
{
    text_zeilenweise tz;
    tz.set_text("Nummer");
    tz.zeile_anhaengen("Bezeichnung");
    return tz;
}

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(kostenstelle k1, kostenstelle k2)
{
    bool returnbool = true;
    if(k1.nr() != k2.nr())
    {
        returnbool = false;
    }
    if(k1.bez() != k2.bez())
    {
        returnbool = false;
    }
    return returnbool;
}
bool operator !=(kostenstelle k1, kostenstelle k2)
{
    bool returnbool = true;
    if(k1.nr() != k2.nr())
    {
        returnbool = false;
    }
    if(k1.bez() != k2.bez())
    {
        returnbool = false;
    }
    if(returnbool == true)
    {
        return false;
    }else
    {
        return true;
    }
}





