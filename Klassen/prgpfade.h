#ifndef PRGPFADE_H
#define PRGPFADE_H

#include <QString>
#include <QDir>

class prgpfade
{
public:
    prgpfade();
    void ordner_erstellen();

    QString name_inifile();
    QString name_KoStFile();
    QString name_UserFile();

    QString path_prg();
    QString path_netw();
    QString path_inifile();
    QString path_KoStFile();
    QString path_UserFile();


private:
    //ini-Dateien:
    QString Inifile;
    QString KoStFile;
    QString UserFile;

};

#endif // PRGPFADE_H
