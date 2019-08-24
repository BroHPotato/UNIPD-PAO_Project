#ifndef FILM_H
#define FILM_H

#include "abstractitem.h"
#include "container.h"
#include <QString>
#include <stdexcept>

class Film : public AbstractItem
{
public:
    Film(double s=0.0, QString t="Nuovo Film", QString d="Non é presente una descrizione", QString f="non definito");
    virtual bool CheckFormat(const QString& f) const;
    virtual QString GetType() const;
    virtual int GetSizeData();
private:
    Container<QString> aviabletype;
};
static QString type="Film";


#endif // FILM_H
