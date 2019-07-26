#ifndef GENERICFILE_H
#define GENERICFILE_H

#include "abstractitem.h"
#include <QString>

class GenericFile : public AbstractItem
{
public:
    GenericFile(double s, QString t, QString d, QString f){
        SetFormat(f);
        SetDesc(d);
        SetTitle(t);
        SetSize(s);
    }
    virtual bool CheckFormat(const QString&) const {return true;}
    virtual int GetSizeData(){
        return 4;
    }
private:
};

#endif // GENERICFILE_H
