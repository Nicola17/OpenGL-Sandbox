#ifndef ABSTRACTLOG_H
#define ABSTRACTLOG_H

class AbstractLog{
public:
    ~AbstractLog(){}
    virtual void clear()=0;
    virtual void display()=0;
};

#endif // ABSTRACTLOG_H
