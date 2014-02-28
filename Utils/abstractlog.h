#ifndef ABSTRACTLOG_H
#define ABSTRACTLOG_H

#include <string>

class AbstractLog{
public:
    virtual ~AbstractLog(){}
    virtual void clear()=0;
    virtual void display(const std::string& d)=0;
};

#endif // ABSTRACTLOG_H
