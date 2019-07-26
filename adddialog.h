#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include<QDialog>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QGridLayout>
#include<QComboBox>
#include<QStringList>
#include<QTextEdit>

class AddDialog : public QDialog
{
public:
    AddDialog(QString t, QWidget* parent=nullptr);
    QComboBox *typeItem;
    QLineEdit *nameItem;
    QTextEdit *descItem;
    QLineEdit *sizeItem;
    QLineEdit *formatItem;
private:
    QLabel *nameItemLabel;
    QLabel *descItemLabel;
    QLabel *sizeItemLabel;
    QLabel *formatItemLabel;
    QLabel *typeItemLabel;
    QPushButton *cancelButton;
    QPushButton *okButton;
};

#endif // ADDDIALOG_H
