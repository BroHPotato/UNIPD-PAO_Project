#ifndef TABWINDOW_H
#define TABWINDOW_H

#include <QTabWidget>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QAbstractButton>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>
#include "model.h"
#include "singletab.h"

class TabWindow : public QTabWidget
{
    Q_OBJECT

public:
    TabWindow(QWidget *parent=nullptr);
    void readFromFile(QString fileName);
    void writeToFile(QString fileName);

public slots:
    void removeT();
    void addT();
    void updateT(QString);
    void resetT();
signals:
    void disableSave();
    void enableSave();

private:
    void addT(QString t);
    Container<SingleTab*> tabs;
    QLabel* instructions;
 };
#endif // TABWINDOW_H
