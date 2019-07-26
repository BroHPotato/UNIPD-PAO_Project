#include "tabwindow.h"

TabWindow::TabWindow(QWidget *parent) : QTabWidget(parent) {
    instructions=new QLabel("Non ci son librerie.\nSeleziona il menu 'Strumenti'->'Aggiungi libreria' per aggiungere una libreria."
                            "\nOppure scegli 'File'->'Apri' per caricare un salvataggio");
    instructions->setAlignment(Qt::AlignCenter);
    addTab(instructions, "Istruzioni");

}

void TabWindow::addT(){
    AddDialogLib aDialog("Aggiungi libreria");

    if(aDialog.exec()){
        QString t=aDialog.nameLib->text();
        tabs.PushBack(new SingleTab(t, this));
        removeTab(indexOf(instructions));
        addTab(tabs[tabs.GetSize()-1],t);
    }
}
void TabWindow::addT(QString t){
    tabs.PushBack(new SingleTab(t, this));
    removeTab(indexOf(instructions));
    addTab(tabs[tabs.GetSize()-1],t);

}
void TabWindow::removeT(){
    SingleTab* p =static_cast<SingleTab*>(sender());
    int index = indexOf(p);

    removeTab(index);
    tabs.Remove(tabs.GetNodo(p));
    if(tabs.GetSize()==0)
        addTab(instructions, "Istruzioni");
}

void TabWindow::updateT(QString t){
    SingleTab* p =static_cast<SingleTab*>(sender());
    int index = indexOf(p);
    setTabText(index,t);
}
void TabWindow::readFromFile(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Impossibile aprie il file",
            file.errorString());
        return;
    }
    //remove all tabs
    QTextStream file_text(&file);
    QString json_string;
    json_string = file_text.readAll();
    file.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument json_doc=QJsonDocument::fromJson(json_bytes);

    QJsonArray json =json_doc.array();

    for(int i=0;i<json.count();++i){
        QJsonObject lib;
        QJsonObject det;
        lib=json[i].toObject();
        addT(lib.value("Name").toString());
        det=json[i].toObject();
        tabs[tabs.GetSize()-1]->Populate(det);
    }
}
void TabWindow::writeToFile(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, "Impossibile aprie il file", file.errorString());
        return;
    }
    QJsonArray filejson;

    for(int i=0;i<tabs.GetSize();++i){
        filejson.append(tabs[i]->SaveLib());
    }
    QJsonDocument saveFile(filejson);
    file.write(saveFile.toJson());
}
