#include"abstractitem.h"

double AbstractItem::GetSize() const {
    return size;
}
QString AbstractItem::GetTitle() const {
    return title;
}
QString AbstractItem::GetDesc() const {
    return desc;
}
QString AbstractItem::GetFormat() const {
    return format;
}
void AbstractItem::SetSize(const double& i) {
    if(i>=0)
        size=i;
    else
        throw(std::out_of_range("Dimensione non valida"));
}
void AbstractItem::SetTitle(const QString& t) {
    title=t;
}
void AbstractItem::SetDesc(const QString& d) {
    desc=d;
}
void AbstractItem::SetFormat(const QString& f) {
    if(this->CheckFormat(f))
        format=f;
    else
        throw(std::invalid_argument("Formato non valido"));
}
