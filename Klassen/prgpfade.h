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
    QString name_MitarbFile();

    QString path_prg();
    QString path_netw();
    QString path_inifile();
    QString path_KoStFile();
    QString path_UserFile();
    QString path_MitarbFile();
    QDir dir_import_az();


private:
    //ini-Dateien:
    QString Inifile;
    QString KoStFile;
    QString UserFile;
    QString MitarbFile;
    QString ImportDirAZ;

};

#endif // PRGPFADE_H
