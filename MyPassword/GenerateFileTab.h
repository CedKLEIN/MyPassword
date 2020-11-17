#pragma once

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class FacAccount;

class GenerateFileTab : public QWidget
{
    Q_OBJECT
public:
    GenerateFileTab(FacAccount &iFacAccount);
    GenerateFileTab(GenerateFileTab const&)=delete;
    GenerateFileTab& operator=(GenerateFileTab const&)=delete;
    void onTabSelected();

public slots:
    void fillTextEdit();
    void saveTextInFile();

private:
    FacAccount& _facAccount;
    QLabel _titleLabel{tr("Generate account in text file")};
    QLabel _outputSaveFileLabel;
    QStringList _textStringList;
    QPushButton _generateTextButt{tr(" Generate text")};
    QPushButton _saveTextButt{tr(" Save in a file")};
    QTextEdit _textEdit;
    QHBoxLayout _buttLayout;
    QVBoxLayout _mainLayout;

};
