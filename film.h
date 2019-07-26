#ifndef FILM_H
#define FILM_H

#include "abstractitem.h"
#include "container.h"
#include <QString>
#include "stdexcpt.h"

class Film : public AbstractItem
{
public:
    Film(double s=0.0, QString t="Nuovo Film", QString d="Non é presente una descrizione", QString f="non definito") {
        aviabletype.PushBack("mp4");
        aviabletype.PushBack("avi");
        aviabletype.PushBack("mkv");
        this->SetSize(s);
        this->SetTitle(t);
        this->SetDesc(d);
        this->SetFormat(f);
    }
    virtual bool CheckFormat(const QString& f) const{
        if(aviabletype.IsIn(f))
            return true;
        return false;
    }
    virtual int GetSizeData(){
        return 4;
    }
private:
    Container<QString> aviabletype;
};



#endif // FILM_H
