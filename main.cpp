#include <QApplication>
#include <QTableView>
#include <iostream>
#include <tabwindow.h>
#include "model.h"
#include "container.h"
#include "tabwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
 {
    QApplication app(argc, argv);
    MainWindow n;
    n.show();
    return app.exec();
}
