#ifndef SINGLETAB_H
#define SINGLETAB_H

#include <QWidget>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QAbstractButton>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QSizePolicy>
#include <QHeaderView>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include "model.h"
#include "adddialog.h"
#include "adddialoglib.h"

class SingleTab : public QWidget
{
    Q_OBJECT
public:
    explicit SingleTab(QString t="Nuova Libreria",QWidget *parent = nullptr);
    QString GetTitle()const;
    void Populate(const QJsonObject& json);
    QJsonObject SaveLib() const;
signals:
    void updateName(QString);
    void removeT();
private slots:
    void addEntry();
    void viewEntry();
    void editEntry();
    void removeEntry();
    void editLibrary();
    void research(QString);
public slots:
    void removeTab(){emit removeT();}
private:
    QString title;
    QTableView * view;
    Model * model;
    QSortFilterProxyModel *proxyModel;
    QLabel* resLabel;
    QComboBox* resFilter;
    QAbstractButton* addData;
    QAbstractButton* viewData;
    QAbstractButton* editData;
    QAbstractButton* removeData;
    QAbstractButton* editLib;
    QAbstractButton* removeLib;
    QGroupBox* Bgroup;
    QLineEdit* searchBar;

    QHBoxLayout* layout;
    QVBoxLayout* blayout;
};

#endif // SINGLETAB_H
