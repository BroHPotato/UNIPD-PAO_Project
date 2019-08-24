#include"image.h"

Image::Image(double s, QString t, QString d, QString f) {
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
 bool Image::CheckFormat(const QString& f) const{
    if(aviabletype.IsIn(f))
        return true;
    return false;
}
int Image::GetSizeData(){
    return 5;
}
QString Image::GetType() const{
    return typefile;
}
