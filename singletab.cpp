#include "singletab.h"

SingleTab::SingleTab(QString t, QWidget *parent) : QWidget(parent)
{
    title=t;

    model = new Model(this);

    proxyModel= new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setDynamicSortFilter(true);

    view=new QTableView(this);
    view->setModel(proxyModel);
    view->setSortingEnabled(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->verticalHeader()->hide();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setSelectionMode(QAbstractItemView::MultiSelection);
    view->setContentsMargins(0,0,0,0);

    resLabel=new QLabel("Ricerca per");
    resFilter=new QComboBox;
    resFilter->addItem("Nome file");
    resFilter->addItem("Descrizione");
    resFilter->addItem("Dimensione");
    resFilter->addItem("Estensione");
    resFilter->addItem("Categoria");
    connect(resFilter, SIGNAL(currentIndexChanged(QString)), this, SLOT(research(QString)));

    searchBar=new QLineEdit();
    searchBar->setPlaceholderText("Ricerca");
    connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(research(QString)));

    addData=new QPushButton("Aggiungi file");
    connect(addData,SIGNAL(clicked()),this, SLOT(addEntry()));

    viewData=new QPushButton("Visualizza file");
    connect(viewData,SIGNAL(clicked()),this, SLOT(viewEntry()));

    editData=new QPushButton("Modifica file");
    connect(editData,SIGNAL(clicked()),this, SLOT(editEntry()));

    removeData=new QPushButton("Rimuovi file");
    connect(removeData,SIGNAL(clicked()),this, SLOT(removeEntry()));

    editLib=new QPushButton("Modifica libreria");
    connect(editLib,SIGNAL(clicked()),this, SLOT(editLibrary()));
    connect(this,SIGNAL(updateName(QString)),parent,SLOT(updateT(QString)));

    removeLib=new QPushButton("Rimuovi libreria");
    connect(removeLib,SIGNAL(clicked()),this, SLOT(removeTab()));
    connect(this,SIGNAL(removeT()),parent,SLOT(removeT()));

    blayout=new QVBoxLayout;
    blayout->addWidget(resLabel);
    blayout->addWidget(resFilter);
    blayout->addWidget(searchBar);
    blayout->addSpacing(20);
    blayout->addWidget(addData);
    blayout->addWidget(viewData);
    blayout->addWidget(editData);
    blayout->addWidget(removeData);
    blayout->addWidget(editLib);
    blayout->addWidget(removeLib);
    blayout->setSizeConstraint(QLayout::SetFixedSize);
    Bgroup=new QGroupBox(this);
    Bgroup->setLayout(blayout);

    layout=new QHBoxLayout;
    layout->addWidget(view);
    layout->addWidget(Bgroup,0,Qt::AlignTop);

    editData->setDisabled(true);
    removeData->setDisabled(true);

    setLayout(layout);
}

void SingleTab::viewEntry(){
    QTableView *temp = view;
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index, i;
    QString t;
    QString d;
    QString f;
    double s = 0.0;
    int row = -1;
    if(indexes.size()==0){
        QMessageBox::information(this, "Attenzione", "Selezionare una riga prima di procedere");
    }else{
        foreach (index, indexes) {

            row = proxy->mapToSource(index).row();
            i = model->index(row, 0, QModelIndex());
            QVariant varTitle = model->data(i, Qt::DisplayRole);
            t = varTitle.toString();

            i = model->index(row, 1, QModelIndex());
            QVariant varDesc = model->data(i, Qt::DisplayRole);
            d = varDesc.toString();

            i = model->index(row, 2, QModelIndex());
            QVariant varSize = model->data(i, Qt::DisplayRole);
            s = varSize.toDouble();

            i = model->index(row, 3, QModelIndex());
            QVariant varFormat= model->data(i, Qt::DisplayRole);
            f= varFormat.toString();
        }

        AddDialog aDialog("Visualizza file");

        aDialog.typeItem->setCurrentText(model->dataType(i,Qt::DisplayRole).toString());
        aDialog.typeItem->setDisabled(true);
        aDialog.nameItem->setText(t);
        aDialog.nameItem->setDisabled(true);
        aDialog.descItem->setText(d);
        aDialog.descItem->setDisabled(true);
        aDialog.formatItem->setText(f);
        aDialog.formatItem->setDisabled(true);
        aDialog.sizeItem->setText(QString::number(s));
        aDialog.sizeItem->setDisabled(true);

        aDialog.exec();
    }
}

void SingleTab::addEntry()
{
    AddDialog aDialog("Aggiungi file");

    if (aDialog.exec()) {
        QString type=aDialog.typeItem->currentText();
        QString name = aDialog.nameItem->text();
        QString desc = aDialog.descItem->toPlainText();
        QString format = aDialog.formatItem->text();
        double size = aDialog.sizeItem->text().toDouble();
        try {
            AbstractItem* p;
            if(type=="File Generico")
                p=new GenericFile(size,name,desc,format);
            else if (type=="Film")
                p=new Film(size,name,desc,format);
            else if (type=="Immagine")
                p=new Image(size,name,desc,format);
            else
                throw std::logic_error("Categoria non supportata");

            model->insertRows(0, 1, QModelIndex());
            QModelIndex index = model->index(0, 0, QModelIndex());
            model->setDataItem(index, QVariant::fromValue(p), Qt::EditRole);

        } catch (std::exception& e) {
            QMessageBox::information(this, "Errore ",e.what());
        }
    }
    if(model->rowCount()!=0){
        editData->setDisabled(false);
        removeData->setDisabled(false);
    }
}
void SingleTab::editEntry()
{
    QTableView *temp = view;
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index, i;
    QString t;
    QString d;
    QString f;
    double s = 0.0;
    int row = -1;
    if(indexes.size()==0){
        QMessageBox::information(this, "Attenzione", "Selezionare una riga prima di procedere");
    }else{
        foreach (index, indexes) {

            row = proxy->mapToSource(index).row();
            i = model->index(row, 0, QModelIndex());
            QVariant varTitle = model->data(i, Qt::DisplayRole);
            t = varTitle.toString();

            i = model->index(row, 1, QModelIndex());
            QVariant varDesc = model->data(i, Qt::DisplayRole);
            d = varDesc.toString();

            i = model->index(row, 2, QModelIndex());
            QVariant varSize = model->data(i, Qt::DisplayRole);
            s = varSize.toDouble();

            i = model->index(row, 3, QModelIndex());
            QVariant varFormat= model->data(i, Qt::DisplayRole);
            f= varFormat.toString();
        }

        AddDialog aDialog("Modifica file");

        try {
            aDialog.typeItem->setCurrentText(model->dataType(i,Qt::DisplayRole).toString());
            aDialog.typeItem->setDisabled(true);
            aDialog.nameItem->setText(t);
            aDialog.descItem->setText(d);
            aDialog.formatItem->setText(f);
            aDialog.sizeItem->setText(QString::number(s));

            if (aDialog.exec()) {
                QString name = aDialog.nameItem->text();
                QString desc = aDialog.descItem->toPlainText();
                QString format = aDialog.formatItem->text();
                double size = aDialog.sizeItem->text().toDouble();
                if (name != t) {
                    i = model->index(row, 0, QModelIndex());
                    model->setData(i, name, Qt::EditRole);
                }
                if (desc != d) {
                    i = model->index(row, 1, QModelIndex());
                    model->setData(i, desc, Qt::EditRole);
                }
                if (std::abs(size-s)<std::numeric_limits<double>::epsilon() || std::abs(size-s)>std::numeric_limits<double>::epsilon()) {
                    i = model->index(row, 2, QModelIndex());
                    model->setData(i, s, Qt::EditRole);
                }
                if (format != f) {
                    i = model->index(row, 3, QModelIndex());
                    model->setData(i, format, Qt::EditRole);
                }
            }
        } catch (std::exception& e) {
            QMessageBox::information(this, "Errore ",e.what());
        }
    }
}

void SingleTab::removeEntry()
{
    QTableView *temp = view;
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index;
    if(indexes.size()==0){
        QMessageBox::information(this, "Attenzione", "Selezionare una riga prima di procedere");
    }else{
        foreach (index, indexes) {
            int row = proxy->mapToSource(index).row();
            model->removeRows(row, 1, QModelIndex());
        }
        if(model->rowCount()==0){
            editData->setDisabled(true);
            removeData->setDisabled(true);
        }

    }
}

void SingleTab::editLibrary()
{
    AddDialogLib aDialog("Modifica libreria");

    if(aDialog.exec()){
        if(aDialog.nameLib->text()!=title){
            title=aDialog.nameLib->text();
            emit updateName(title);
        }
    }
}

void SingleTab::research(QString res)
{
    int col=0;
    QString tores="";
    if(dynamic_cast<QComboBox*>(sender())){
        if(res=="Nome file")
            col=0;
        else if (res=="Descrizione")
            col=1;
        else if (res=="Dimensione")
            col=2;
        else if (res=="Estensione")
            col=3;
        else if (res=="Categoria")
            col=4;
        tores=searchBar->text();
    }else if(dynamic_cast<QLineEdit*>(sender())){
        col=resFilter->currentIndex();
        tores=res;
    }
    proxyModel->setFilterRegExp(QRegExp(tores, Qt::CaseInsensitive));
    proxyModel->setFilterKeyColumn(col);
    proxyModel->sort(col, Qt::AscendingOrder);

}

QString SingleTab::GetTitle()const
{
    return  title;
}

void SingleTab::Populate(const QJsonObject& json){
    QJsonArray entrys=json.value("Entrys").toArray();
    title=json.value("Name").toString();

    for(int i=0; i<entrys.count();++i){
        QJsonObject entry=entrys[i].toObject();

        QString type=entry.value("Type").toString();
        QString name = entry.value("Titolo").toString();
        QString desc = entry.value("Desc").toString();
        QString format = entry.value("Format").toString();
        double size = entry.value("Size").toDouble();
        try {
            AbstractItem* p;
            if(type=="File Generico")
                p=new GenericFile(size,name,desc,format);
            else if (type=="Film")
                p=new Film(size,name,desc,format);
            else if (type=="Immagine")
                p=new Image(size,name,desc,format);
            else
                throw std::logic_error("Categoria non supportata");

            model->insertRows(0, 1, QModelIndex());
            QModelIndex index = model->index(0, 0, QModelIndex());
            model->setDataItem(index, QVariant::fromValue(p), Qt::EditRole);

        } catch (std::exception& e) {
            QMessageBox::information(this, "Errore",e.what());
        }
    }
    if(model->rowCount()!=0){
        editData->setDisabled(false);
        removeData->setDisabled(false);
    }
}

QJsonObject SingleTab::SaveLib() const{
    QJsonObject json;

    int row = model->rowCount();
    QJsonArray jarray;
    for(int i=0; i<row; ++i){
        QJsonObject jobj;
        QModelIndex index=model->index(i,0);
        jobj["Titolo"]=model->data(index,Qt::DisplayRole).toString();
        index=model->index(i,1);
        jobj["Desc"]=model->data(index,Qt::DisplayRole).toString();
        index=model->index(i,2);
        jobj["Size"]=model->data(index,Qt::DisplayRole).toDouble();
        index=model->index(i,3);
        jobj["Format"]=model->data(index,Qt::DisplayRole).toString();
        index=model->index(i,4);
        jobj["Type"]=model->data(index,Qt::DisplayRole).toString();
        jarray.prepend(jobj);
    }
    json["Entrys"]=jarray;
    json["Name"]=title;
    return json;
}
