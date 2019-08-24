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
    virtual double GetSize() const;
    virtual QString GetTitle() const;
    virtual QString GetDesc() const;
    virtual QString GetFormat() const;
    virtual bool CheckFormat(const QString&) const=0;
    virtual QString GetType() const=0;

    virtual int GetSizeData()=0;
    virtual void SetSize(const double& i);
    virtual void SetTitle(const QString& t);
    virtual void SetDesc(const QString& d);
    virtual void SetFormat(const QString& f);

private:
    double size;
    QString title;
    QString desc;
    QString format;
};

#endif // ABSTRACTITEM_H
