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

//-----------------private:
bool kostenstellen::exist(kostenstelle k)
{
 bool retbool = false;
 for(int i=0;i<KoSt.count();i++)
 {
     if(KoSt.at(i)==k)
     {
         retbool = true;
         break;
     }
 }
 return retbool;
}

