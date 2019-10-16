#ifndef THREADS
#define THREADS

#include <QThread>
#include <QString>
//#include <QDebug>


class Threads :  public QThread
{
public:
    explicit Threads(QString s);
    ~Threads();
    void run(void func());
private:
    QString name;
};


#endif // THREADS

