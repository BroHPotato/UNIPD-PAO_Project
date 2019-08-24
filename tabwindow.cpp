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
        emit enableSave();
    }
}
void TabWindow::addT(QString t){
    tabs.PushBack(new SingleTab(t, this));
    removeTab(indexOf(instructions));
    addTab(tabs[tabs.GetSize()-1],t);
    emit enableSave();
}
void TabWindow::removeT(){
    SingleTab* p =static_cast<SingleTab*>(sender());
    int index = indexOf(p);

    removeTab(index);
    tabs.Remove(tabs.GetNodo(p));
    if(tabs.GetSize()==0){
        emit disableSave();
        addTab(instructions, "Istruzioni");
    }
}
void TabWindow::resetT(){
    for (int i=tabs.GetSize()-1;i>=0;--i) {
        tabs[i]->removeTab();
    }
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
    QTextStream file_text(&file);
    QString json_string;
    json_string = file_text.readAll();
    file.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument json_doc=QJsonDocument::fromJson(json_bytes);

    QJsonArray json =json_doc.array();
    try {
        for(int i=0;i<json.count();++i){
            QJsonObject lib;
            lib=json[i].toObject();
            if (!lib.contains("Entrys") || !lib.contains("Name") )
                throw (std::invalid_argument("File JSON non valido o corrotto.\nProvare con un altro file"));
        }

        clear();
        tabs.Clear();

        for(int i=0;i<json.count();++i){
            QJsonObject lib;
            lib=json[i].toObject();
            addT(lib.value("Name").toString());
            tabs[tabs.GetSize()-1]->Populate(lib);
        }
    } catch (std::exception& e) {
        QMessageBox::information(this, "Errore caricamento",e.what());
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
