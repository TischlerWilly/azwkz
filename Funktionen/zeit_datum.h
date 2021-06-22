#ifndef ZEIT_DATUM_H
#define ZEIT_DATUM_H

#include <QTime>
#include <QDate>

#include <QMessageBox>

#include "Funktionen/text.h"

QTime text_zu_qtime(QString s);

QDate text_zu_qdate(QString s);

//-----------------------------------------Operatoren:
QTime operator -(QTime t1, QTime t2);
QTime operator +(QTime t1, QTime t2);

#endif // ZEIT_DATUM_H
