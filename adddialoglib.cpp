#include "adddialoglib.h"

AddDialogLib::AddDialogLib(QString t, QWidget* parent): QDialog(parent)
{
    nameLabel = new QLabel("Nome libreria");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    nameLib = new QLineEdit;
    nameLib->setPlaceholderText("Titolo libreria");

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameLib, 0, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));

    setWindowTitle(t);
}
