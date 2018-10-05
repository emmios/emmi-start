#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include "threads.h"

QStringList qlist, qlist2, qlist3;

void windowManager()
{
    QProcess *process = new QProcess();
    //process->start("xfwm4", qlist);
    process->start("/home/shenoisz/Documents/estudos/C/openbox/openbox-3.6.1/openbox/.libs/openbox");
    //process->start("kwin", qlist);
    process->waitForReadyRead();
}

void compositor()
{
    QProcess *process = new QProcess();
    //"-cfC"
    //xcompmgr -c -C -t-5 -l-5 -r4.2 -o.55
    //compton -c
    //qlist3 << "-c" << "-C";
    //process->start("xcompmgr", qlist3);
    //qlist3 << "-c" << "-C";
    qlist3 << "--config" << "/home/shenoisz/compton.conf";
    process->start("compton", qlist3);
    process->waitForStarted();
}

void desktop()
{
    QProcess *process = new QProcess();
    //qlist2 << "--desktop";
    //qlist2 << "--bg-fill" << "/home/shenoisz/Pictures/desktop-background/07.jpg";
    //process->start("/home/shenoisz/Documents/estudos/QT-creator/build-desktop-dev-Qt_5_5_1_qt5-Release/desktop-dev", qlist);
    //process->start("/home/shenoisz/Documents/estudos/QT-creator/build-XWidget-Qt_5_5_1_qt5-Release/XWidget", qlist);
    //process->start("feh", qlist2);
    //process->start("xfdesktop", qlist);
    //process->start("pcmanfm", qlist2);
    //process->start("/home/shenoisz/Documents/estudos/QT-creator/build-Neon_Desktop-Qt_5_5_1_qt5-Release/Neon_Desktop", qlist2);
    process->start("/home/shenoisz/Documents/estudos/QT-creator/build-DesktopManager-Desktop_Qt_5_7_1_GCC_64bit-Release/DesktopManager");
}

void dock()
{
    QProcess *process = new QProcess();
    process->start("plank");
}

void panel()
{
    //exec xrandr --output eDP1 --dpi 100
    QProcess *process2 = new QProcess();
//    QStringList argumments;
//    argumments << "--output" << "eDP1" << "--dpi" << "96x96";
//    process2->start("xrandr", argumments);
//    process2->close();

    process2->start("/home/shenoisz/Documents/estudos/QT-creator/build-Neon_Panel-Desktop_Qt_5_7_1_GCC_64bit-Release/Neon_Panel");
    process2->waitForStarted();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Threads *t1 = new Threads("windowManager");
    Threads *t2 = new Threads("compositor");
    Threads *t3 = new Threads("dock");
    //Threads *t4 = new Threads("desktop");

    desktop();
    panel();

    t1->run(windowManager);
    t2->run(compositor);
    t3->run(dock);

    return a.exec();
}

