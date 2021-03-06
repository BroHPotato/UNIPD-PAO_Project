#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    TabWidget = new TabWindow(this);
    setCentralWidget(TabWidget);
    createMenus();
    setMinimumWidth(800);
    setMinimumHeight(400);
    setWindowTitle("Progetto PAO");
}
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("File");

    openAct = new QAction("Apri", this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()),this, SLOT(openFile()));

    saveAct = new QAction("Salva", this);
    saveAct->setEnabled(false);
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()),this, SLOT(saveFile()));

    fileMenu->addSeparator();

    exitAct = new QAction("Esci", this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()),this, SLOT(close()));

    toolMenu = menuBar()->addMenu("Strumenti");

    addAct = new QAction("Aggiungi libreria", this);
    toolMenu->addAction(addAct);
    connect(addAct, SIGNAL(triggered()),TabWidget, SLOT(addT()));

    resetAct = new QAction("Nuova raccolta", this);
    toolMenu->addAction(resetAct);
    connect(resetAct, SIGNAL(triggered()),TabWidget, SLOT(resetT()));

    connect(TabWidget, SIGNAL(enableSave()), this, SLOT(enableSave()));
    connect(TabWidget, SIGNAL(disableSave()), this, SLOT(disableSave()));
}

void MainWindow::enableSave(){
    saveAct->setEnabled(true);
}

void MainWindow::disableSave(){
    saveAct->setEnabled(false);
}
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Apri librerie",QString(),"JSON(*.json)");
    if (!fileName.isEmpty()) {
        TabWidget->readFromFile(fileName);
    }
}
void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Salva librerie",QString(),"JSON(*.json)");
    if (!fileName.isEmpty()) {
        TabWidget->writeToFile(fileName);
    }
}
