#pragma once

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class FacAccount;
class ILog;

class GenerateFileTab : public QWidget
{
    Q_OBJECT
public:
    GenerateFileTab(FacAccount &iFacAccount,ILog&);
    GenerateFileTab(GenerateFileTab const&)=delete;
    GenerateFileTab& operator=(GenerateFileTab const&)=delete;
    void onTabSelected();

public slots:
    void fillTextEdit();
    void saveTextInFile();

private:
    FacAccount& _facAccount;
    ILog& _log;
    QLabel* _titleLabel{new QLabel{tr("Generate data account in text file")}};
    QLabel* _outputSaveFileLabel{new QLabel};
    QStringList* _textStringList{new QStringList};
    QPushButton* _generateTextButt{new QPushButton{tr(" Generate text")}};
    QPushButton* _saveTextButt{new QPushButton{tr(" Save in a file")}};
    QTextEdit* _textEdit{new QTextEdit};
    QHBoxLayout* _buttLayout{new QHBoxLayout};
    QVBoxLayout* _mainLayout{new QVBoxLayout};

};
