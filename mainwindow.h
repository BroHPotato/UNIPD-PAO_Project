#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QSizePolicy>
#include"tabwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void openFile();
    void saveFile();
public slots:
    void enableSave();
    void disableSave();
private:
    void createMenus();

    TabWindow *TabWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *resetAct;
};
#endif // MAINWINDOW_H
