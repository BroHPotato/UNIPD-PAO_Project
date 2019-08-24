#include "adddialog.h"

AddDialog::AddDialog(QString t, QWidget* parent): QDialog(parent)
{
    nameItemLabel=new QLabel("Nome file");
    descItemLabel=new QLabel("Descrizione");
    sizeItemLabel=new QLabel("Dimensione file");
    formatItemLabel=new QLabel("Estensione file");
    typeItemLabel=new QLabel("Categoria");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");


    typeItem= new QComboBox;
    typeItem->addItem("File Generico");
    typeItem->addItem("Film");
    typeItem->addItem("Immagine");

    nameItem=new QLineEdit;
    nameItem->setPlaceholderText("Titolo");

    descItem=new QTextEdit;

    sizeItem=new QLineEdit;
    sizeItem->setPlaceholderText("in KB");
    sizeItem->setValidator(new QDoubleValidator(0,INFINITY,1000));

    formatItem=new QLineEdit;
    formatItem->setPlaceholderText("es. mp4 o png");

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(nameItemLabel,0,0);
    gLayout->addWidget(nameItem,0,1);
    gLayout->addWidget(sizeItemLabel,0,2);
    gLayout->addWidget(sizeItem,0,3);
    gLayout->addWidget(descItemLabel,1,0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(descItem,1,1,2,4);
    gLayout->addWidget(typeItemLabel,3,0);
    gLayout->addWidget(typeItem,3,1);
    gLayout->addWidget(formatItemLabel,3,2);
    gLayout->addWidget(formatItem,3,3);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));

    setWindowTitle(t);
}
