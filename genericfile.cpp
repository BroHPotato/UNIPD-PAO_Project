#include"genericfile.h"

GenericFile::GenericFile(double s, QString t, QString d, QString f){
    SetFormat(f);
    SetDesc(d);
    SetTitle(t);
    SetSize(s);
}
bool GenericFile::CheckFormat(const QString&) const {
    return true;
}
QString GenericFile::GetType() const{
    return typefile;
}
int GenericFile::GetSizeData(){
    return 5;
}
