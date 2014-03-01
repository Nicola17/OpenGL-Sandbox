#ifndef ABSTRACTLOG_H
#define ABSTRACTLOG_H

#include <string>
#include <sstream>

class AbstractLog{
public:
    virtual ~AbstractLog(){}
    virtual void clear()=0;
    virtual void display(const std::string& d)=0;
};

#define SECURE_LOG(log,text){if((log)!=nullptr){(log)->display(text);}}
#define SECURE_LOG_VAL(log,text,v){if((log)!=nullptr){\
                                        std::stringstream ss;\
                                        ss << text << ": " << v;\
                                        (log)->display(ss.str());\
                                    }}
#define SECURE_LOG_VERBOSE(log,text){if(_verbose){SECURE_LOG(log,text)}}
#define SECURE_LOG_VAL_VERBOSE(log,text,v){if(_verbose){SECURE_LOG_VAL(log,text,v)}}

#endif // ABSTRACTLOG_H
