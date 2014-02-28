#ifndef PTELOG_H
#define PTELOG_H

#include "abstractlog.h"
#include <QPlainTextEdit>

class PTELog: public AbstractLog
{
public:
    PTELog();
    virtual ~PTELog(){}

    virtual void clear();
    virtual void display(const std::string& d);

    void connectPTE(QPlainTextEdit* pte){_pte = pte;}
    void disconnectPTE(){_pte = nullptr;}

public:
    QPlainTextEdit* _pte;
};

#endif // PTELOG_H
