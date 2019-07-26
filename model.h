#ifndef MODEL_H
#define MODEL_H


#include <QObject>
#include <QAbstractListModel>
#include "stdexcpt.h"
#include "container.h"
#include "abstractitem.h"
#include "film.h"
#include "image.h"
#include "genericfile.h"

class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    Model(QObject * parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex()) override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;
    bool setDataItem(const QModelIndex &index, const QVariant &value, int role);
    QVariant dataType(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Container<AbstractItem *> getLib()const;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    Container<AbstractItem *> library;
    QString title;
signals:
};
Q_DECLARE_METATYPE(AbstractItem *)
#endif // MODEL_H
