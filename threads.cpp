#include "threads.h"

Threads::Threads(QString s) : name(s)
{

}

Threads::~Threads()
{
    quit();
}

void Threads::run(void func())
{
    func();
}
