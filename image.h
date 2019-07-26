#ifndef IMAGE_H
#define IMAGE_H

#include "abstractitem.h"
#include "container.h"
#include <QString>


class Image : public AbstractItem
{
public:
    Image(double s, QString t, QString d, QString f) {
        aviabletype.PushBack("png");
        aviabletype.PushBack("jpg");
        aviabletype.PushBack("jpeg");
        if(this->CheckFormat(f)){
            this->SetSize(s);
            this->SetTitle(t);
            this->SetDesc(d);
            this->SetFormat(f);
       }else
            throw(new std::invalid_argument("Formato non valido"));
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
#endif // IMAGE_H
