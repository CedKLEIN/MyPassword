#pragma once

#include "Interface/IUpdateAccountListener.h"

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class FacAccount;
class IDatabase;
class ILog;

class GenerateFileTab : public QWidget
{
    Q_OBJECT
public:
    GenerateFileTab(FacAccount &iFacAccount,IDatabase&,ILog&);
    GenerateFileTab(GenerateFileTab const&)=delete;
    GenerateFileTab& operator=(GenerateFileTab const&)=delete;
    void onTabSelected();

    void addListener(IUpdateAccountListener* iListener){
        _listeners.push_back(iListener);
    }

public slots:
    void importDatafromFile();
    void generateTextEdit();
    void saveTextInFile();

private:
    void fireEventUpdate(){
        for(const auto& listener : _listeners){
            listener->onEventUpdateAccount();
        }
    }

    void addNewAccount(const QStringList&);

    FacAccount& _facAccount;
    IDatabase& _database;
    ILog& _log;

    std::vector<IUpdateAccountListener*> _listeners;

    QLabel* _titleLabel{new QLabel{tr("Generate data account in text file")}};
    QLabel* _outputSaveFileLabel{new QLabel};
    QStringList* _textStringList{new QStringList};
    QPushButton* _importDataFromTextButt{new QPushButton{tr(" Import datat from text file")}};
    QPushButton* _generateTextButt{new QPushButton{tr(" Generate text")}};
    QPushButton* _saveTextButt{new QPushButton{tr(" Save in a file")}};
    QTextEdit* _textEdit{new QTextEdit};
    QHBoxLayout* _buttLayout{new QHBoxLayout};
    QVBoxLayout* _mainLayout{new QVBoxLayout};

};
