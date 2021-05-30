#include "prgpfade.h"

prgpfade::prgpfade()
{
    Inifile     = "einstellungen.ini";
    KoStFile    = "kostenstellen.ini";
    UserFile    = "nutzer.ini";
}

void prgpfade::ordner_erstellen()
{
    QDir dir_prg(path_prg());
    if(!dir_prg.exists())
    {
        dir_prg.mkdir(path_prg());
    }
    QDir dir_user(path_netw());
    if(!dir_user.exists())
    {
        dir_user.mkdir(path_netw());
    }
}

QString prgpfade::name_inifile()
{
    return Inifile;
}
QString prgpfade::name_KoStFile()
{
    return KoStFile;
}
QString prgpfade::name_UserFile()
{
    return UserFile;
}

QString prgpfade::path_prg()
{
    QString tmp;
    tmp = "C:\\Program Files\\azwkz";
    return tmp;
}
QString prgpfade::path_netw()
{
    QString tmp;
    tmp = "T:\\Zeiterfassung\\.azwkz";
    return tmp;
}
QString prgpfade::path_inifile()
{
    QString tmp;
    tmp = path_netw();
    tmp += QDir::separator();
    tmp += Inifile;
    return tmp;
}
QString prgpfade::path_KoStFile()
{
    QString tmp;
    tmp = path_netw();
    tmp += QDir::separator();
    tmp += KoStFile;
    return tmp;
}
QString prgpfade::path_UserFile()
{
    QString tmp;
    tmp = path_netw();
    tmp += QDir::separator();
    tmp += UserFile;
    return tmp;
}



