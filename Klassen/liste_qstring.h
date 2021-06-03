#ifndef LISTE_QSTRING_H
#define LISTE_QSTRING_H

#include <QString>
#include "text_zeilenweise.h"

class liste_QString
{
public:
    liste_QString();
    //set_xy:
    void von_tz(text_zeilenweise tz);
    void vorwecksetzen(QString wert);
    void anhaengen(QString wert);
    void einfuegen(int index, QString wert);
    void einfuegen(int index, text_zeilenweise tz);
    void ersaetzen(int index, QString wert);
    void loeschen(int index);
    void loeschen(int index, int anz_werte);

    //get_xy:
    text_zeilenweise tz(char trennzeichen);
    QString wert(int index);
    text_zeilenweise werte_tz(int index, int anz_werte);
    liste_QString werte_liste(int index, int anz_werte);
    int count();

    //Manipulationen:
    void clear();

private:
    QVector<QString> Vs;
};

#endif // LISTE_QSTRING_H
