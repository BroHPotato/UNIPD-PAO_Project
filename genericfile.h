#ifndef GENERICFILE_H
#define GENERICFILE_H

#include "abstractitem.h"
#include <QString>

class GenericFile : public AbstractItem
{
public:
    GenericFile(double s, QString t, QString d, QString f);
    virtual bool CheckFormat(const QString&) const;
    virtual QString GetType() const;
    virtual int GetSizeData();
private:
    const QString typefile="File generico";
};


#endif // GENERICFILE_H
