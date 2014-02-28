#include "ptelog.h"

PTELog::PTELog():
    _pte(nullptr)
{
}

void PTELog::clear(){
    if(_pte!=nullptr)
        _pte->clear();
}

void PTELog::display(const std::string& d){
    if(_pte!=nullptr)
        _pte->appendPlainText(QString::fromStdString(d));
}
