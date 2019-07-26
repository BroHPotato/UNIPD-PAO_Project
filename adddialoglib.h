#ifndef ADDDIALOGLIB_H
#define ADDDIALOGLIB_H

#include<QDialog>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QGridLayout>

class AddDialogLib : public QDialog
{
    Q_OBJECT
public:
    AddDialogLib(QString t, QWidget* parent=nullptr);
    QLineEdit *nameLib;
private:
    QLabel *nameLabel;
    QPushButton *cancelButton;
    QPushButton *okButton;
};

#endif // ADDDIALOGLIB_H
