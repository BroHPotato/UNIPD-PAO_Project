#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QObject>
#include <QString>
#include <stdexcept>

class AbstractItem
{
public:
    AbstractItem(double s=0.0, QString t="Nuovo File", QString d="Non é presente una descrizione", QString f="non definito") : size(s), title(t), desc(d), format(f) {}
    virtual ~AbstractItem()=default;
    virtual double GetSize() const {return size;}
    virtual QString GetTitle() const {return title;}
    virtual QString GetDesc() const {return desc;}
    virtual QString GetFormat() const {return format;}
    virtual bool CheckFormat(const QString&) const=0;

    virtual int GetSizeData()=0;
    virtual void SetSize(const double& i) {if(i>=0)
                                                size=i;
                                            else
                                                throw(std::out_of_range("Dimensione non valida"));}
    virtual void SetTitle(const QString& t) {title=t;}
    virtual void SetDesc(const QString& d) {desc=d;}
    virtual void SetFormat(const QString& f) {  if(this->CheckFormat(f))
                                                    format=f;
                                                else
                                                    throw(std::invalid_argument("Formato non valido"));
                                             }

private:
    double size;
    QString title;
    QString desc;
    QString format;

signals:

public slots:
};

#endif // ABSTRACTITEM_H
