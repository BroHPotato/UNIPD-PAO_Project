#ifndef IMAGE_H
#define IMAGE_H

#include "abstractitem.h"
#include "container.h"
#include <QString>

class Image : public AbstractItem
{
public:
    Image(double s, QString t, QString d, QString f);
    virtual bool CheckFormat(const QString& f) const;
    virtual int GetSizeData();
    virtual QString GetType() const;
private:
    Container<QString> aviabletype;
    const QString typefile="Immagine";
};

#endif // IMAGE_H
