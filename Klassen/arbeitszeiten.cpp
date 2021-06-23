#include "arbeitszeiten.h"

arbeitszeiten::arbeitszeiten()
{
    liste_QString tabkopf;
    tabkopf.anhaengen("id-scanner");
    tabkopf.anhaengen("Tag");
    tabkopf.anhaengen("Uhrzeit");
    tabkopf.anhaengen("Projekt");
    tabkopf.anhaengen("Kostenstelle");
    ArbZeit.set_tabkopf(tabkopf);
}

//-----------------public:
//-------------set:
bool arbeitszeiten::add(liste_QString z)
{
    bool existiert = false;
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        if(z.tz('\n').text() == ArbZeit.zeile(i).tz('\n').text())
        {
            existiert = true;
            break;
        }
    }
    if(!existiert)
    {
        ArbZeit.zeile_anhaengen(z);
        return false;//Es gab keinen Fehler
    }else
    {
        return  true;//Es gab einen Fehler
    }
}
bool arbeitszeiten::del(liste_QString z)
{
    bool retbool = true;//es gab einen Fehler
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        if(z.tz('\n').text() == ArbZeit.zeile(i).tz('\n').text())
        {
            retbool = false;//Es gab keinen Fehler
            ArbZeit.zeile_entfernen(i);
            break;
        }
    }
    return retbool;
}
void arbeitszeiten::clear()
{
    ArbZeit.clear();
}
void arbeitszeiten::import()
{
    prgpfade pf;
    QDir idir = pf.dir_import_az();
    liste_QString dateien = dateien_erfassen(idir);
    for(int i=0;i<dateien.count();i++)//Datei für Datei einlesen
    {
        QFile f(dateien.qstringlist().at(i));
        text_zeilenweise tz;
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString msg;
            msg = "Fehler beim zugriff auf die Datei \"";
            msg += dateien.qstringlist().at(i);
            msg += "\"!";
            QMessageBox::warning(new QDialog,"Fehler",msg,QMessageBox::Ok);
        }else
        {
            tz.set_text(QString::fromLatin1(f.readAll()));
        }
        for(uint ii=2;ii<tz.zeilenanzahl();ii++)//Zeile für Zeile speichern
        {//Erst in 2. Zeile beginnen weil 1. Zeile Tabellenkpf ist
            text_zeilenweise zeile_tz;
            zeile_tz.set_trennzeichen('\t');
            zeile_tz.set_text(tz.zeile(ii));
            liste_QString zeile;
            QString idscan, tag, zeit, proj, kst;
            idscan = zeile_tz.zeile(4);
            tag = zeile_tz.zeile(5);
            zeit = zeile_tz.zeile(3);
            proj = zeile_tz.zeile(1);
            kst = zeile_tz.zeile(2);
            zeile.anhaengen(idscan);
            zeile.anhaengen(tag);
            zeile.anhaengen(text_links(zeit,"Uhr"));
            zeile.anhaengen(proj);
            zeile.anhaengen(kst);
            add(zeile);
        }
    }
}

//-------------get:
text_zeilenweise arbeitszeiten::tabelle_tz()
{
    text_zeilenweise tab;
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        tab.zeile_anhaengen(ArbZeit.zeile(i).tz(';').text());
    }
    return tab;
}
tabelle_qstring *arbeitszeiten::tabelle()
{
    return &ArbZeit;
}
tabelle_qstring arbeitszeiten::tabelle(QString idscan, QDate von, QDate bis)
{
    tabelle_qstring tab;
    tab.set_tabkopf(ArbZeit.tabkopf());
    for(int i=0;i<ArbZeit.anz_zeilen();i++)
    {
        if(idscan.isEmpty())
        {
            QDate datum_zeile;
            datum_zeile = text_zu_qdate(ArbZeit.wert(i,INDEX_ARBZEIT_TAG));
            if((von <= datum_zeile) && (datum_zeile <= bis))
            {
                tab.zeile_anhaengen(ArbZeit.zeile(i));
            }
        }else
        {
            if(ArbZeit.wert(i, INDEX_ARBZEIT_IDSCAN) == idscan)
            {
                QDate datum_zeile;
                datum_zeile = text_zu_qdate(ArbZeit.wert(i,INDEX_ARBZEIT_TAG));
                if((von <= datum_zeile) && (datum_zeile <= bis))
                {
                    tab.zeile_anhaengen(ArbZeit.zeile(i));
                }
            }
        }
    }
    return tab;
}
tabelle_qstring arbeitszeiten::tagzet(QString idscan, QDate tag, QString& report)
{
    tabelle_qstring tab_ret, tab_import;
    tab_import = tabelle(idscan, tag, tag);
    QTime az_begin, az_ende, dauer_anwesenheit, dauer_pausen, az_dauer;
    dauer_pausen.setHMS(0,0,0);
    bool begin_gesetzt = false;
    for(int i=0;i<tab_import.anz_zeilen();i++)
    {
        QString kst = tab_import.wert(i, INDEX_ARBZEIT_KST);

        //Beginn der Arbeitszeit ermitteln:
        if(kst != "000")
        {
            if(begin_gesetzt == false)
            {
                az_begin = text_zu_qtime(tab_import.wert(i, INDEX_ARBZEIT_UHRZEIT));
                begin_gesetzt = true;
            }
        }

        //Feierabend ermitteln:
        if(i == tab_import.anz_zeilen()-1 )
        {
            if(kst == "000")
            {
                az_ende = text_zu_qtime(tab_import.wert(i, INDEX_ARBZEIT_UHRZEIT));
            }else
            {
                Dialog_zeitabfrage dlg;
                dlg.setWindowTitle("Feierabend nicht gebucht");
                dlg.set_labeltext("Der Feierabend wurde nicht erfasst!\nWann wurde feierabend gemacht?");
                QTime default_time;
                default_time.setHMS(15,0,0);
                dlg.set_default_time(default_time);
                if(dlg.exec() == QDialog::Accepted)
                {
                    az_ende = dlg.zeit();
                }else
                {
                    QMessageBox mb;
                    mb.setText("Tageszettel kann ohne bekannten Feierabend nicht erstellt werden.");
                    mb.setWindowTitle("Tageszettel erstellen");
                    mb.exec();
                    tabelle_qstring tab_ret;
                    return tab_ret;//leere tabelle
                }
            }
        }

        //Pausendauer ermitteln:
        if(i < tab_import.anz_zeilen() - 2)
        {
            if(kst == "000")
            {
                QTime begin_pause, ende_pause, dauer;
                begin_pause = text_zu_qtime(tab_import.wert(i, INDEX_ARBZEIT_UHRZEIT));
                ende_pause = text_zu_qtime(tab_import.wert(i+1, INDEX_ARBZEIT_UHRZEIT));
                dauer = ende_pause - begin_pause;
                dauer_pausen = dauer_pausen + dauer;
            }
        }
    }
    dauer_anwesenheit = az_ende - az_begin;
    az_dauer = dauer_anwesenheit - dauer_pausen;

    report = "Ersteller des Reports:";
    report += "\n";
    report += "user xy";
    report += "\n";
    report += "Erstellt am:";
    report += "\n";
    report += int_to_qstring(QDate::currentDate().year());
    report += ".";
    report += int_to_qstring(QDate::currentDate().month());
    report += ".";
    report += int_to_qstring(QDate::currentDate().day());
    report += "\n";
    report += "\n";
    report += az_begin.toString();
    report += " Arbeitsbegin";
    report += "\n";
    report += az_ende.toString();
    report += " Feierabend";
    report += "\n";
    report += "\n";
    report += dauer_anwesenheit.toString();
    report += " Anwesenheitszeit";
    report += "\n";
    report += "\n";
    report += dauer_pausen.toString();
    report += " Dauer Pause";
    QTime mindpause;
    mindpause.setHMS(0,55,0);
    if(dauer_pausen < mindpause)
    {
        report += "\tAchtung eventuell Pause nicht gescannt!";
    }
    report += "\n";
    report += "\n";
    report += az_dauer.toString();
    report += " Dauer Arbeit";
    report += "\n";

    //Projektzeiten ermitteln:
    for(int i=0;i<tab_import.anz_zeilen();i++)
    {

    }

    return tab_ret;
}



