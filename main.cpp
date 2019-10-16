#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QFile>

#include "threads.h"


QStringList qlist, qlist2;
bool compose = false;
bool openboxFix = false;


void windowManager()
{
    QProcess *process = new QProcess();
    QFile file("/usr/bin/startkde_override");

    if(file.exists())
    {
        qlist << "/usr/bin/startkde_override";
        process->start("bash", qlist);
    }
    else
    {
        QFile openbox("/usr/bin/openbox");

        if(openbox.exists())
        {
            compose = true;
            openboxFix = true;
            process->start("openbox");
        }
        else
        {
            QFile xfwm4("/usr/bin/xfwm4");

            if(xfwm4.exists())
            {
                compose = true;
                process->start("xfwm4");
            }
        }
    }

    //Threads::sleep(5);

    //process->start("xfwm4", qlist);
    //

    //process->start("kwin", qlist);
}

void dacoration()
{
    //if (openboxFix) Threads::sleep(8);
    QProcess *process = new QProcess();
    QFile compton("/usr/bin/compton");

    if (compton.exists())
    {
        QString username = qgetenv("USER");
        QString conf = "/home/" + username + "/compton.conf";
        QFile file(conf);

        if (file.exists())
        {
            qlist2 << "--config" << conf;
            process->start("compton", qlist2);
        }
        else
        {
            qlist2 << "--config" << "/usr/share/compton/compton.conf";
            process->start("compton", qlist2);
        }
    }
    else
    {
        qlist2 << "-c" << "-C" << "-t-5" << "-l-5" << "-r4.2" << "-o.55";
        process->start("xcompmgr", qlist2);
    }
}

void desktop()
{
    QProcess *process = new QProcess();
    process->start("synth-desktop");
}


void panel()
{
    Threads::sleep(5);
    QProcess *process2 = new QProcess();
    process2->start("/usr/bin/synth-panel");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Threads *t1 = new Threads("desktop");
    Threads *t2 = new Threads("windowManager");
    Threads *t3 = new Threads("panel");

    t1->run(desktop);
    t2->run(windowManager);
    t3->run(panel);

    if (compose)
    {
        Threads *t4 = new Threads("compositor");
        t4->run(dacoration);
    }

    if (openboxFix) {
        Threads::sleep(5);
        QProcess *process = new QProcess();
        qlist << "--replace";
        process->start("openbox", qlist);
    }

    return a.exec();
}

