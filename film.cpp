#include"film.h"

Film::Film(double s, QString t, QString d, QString f) {
    aviabletype.PushBack("mp4");
    aviabletype.PushBack("avi");
    aviabletype.PushBack("mkv");
    this->SetSize(s);
    this->SetTitle(t);
    this->SetDesc(d);
    this->SetFormat(f);
}
bool Film::CheckFormat(const QString& f) const{
    if(aviabletype.IsIn(f))
        return true;
    return false;
}
QString Film::GetType() const{
    return type;
}
int Film::GetSizeData(){
    return 5;
}
