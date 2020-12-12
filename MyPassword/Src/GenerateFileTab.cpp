#include "GenerateFileTab.h"

#include "Account.h"
#include "Interface/IDatabase.h"
#include "Interface/ILog.h"
#include "Utility.h"

#include <QScrollBar>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <fstream>

const QString GFT_LOGIN{QObject::tr("Login:")};
const QString GFT_PASSWORD{QObject::tr("Password:")};
const QString GFT_DETAILS{QObject::tr("Details:")};
const QString GFT_SEVERITY{QObject::tr("Severity:")};

GenerateFileTab::GenerateFileTab(FacAccount& iFacAccount,
                                 IDatabase& iDatabase,
                                 ILog& iLog):
    _facAccount{iFacAccount},
    _database{iDatabase},
    _log{iLog}
{
    setMinimumWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QTEXTEDIT());

    _titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel->setStyleSheet(Utility::SET_TEXT_SIZE(40)+
                               Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _importDataFromTextButt->setIcon(QIcon(QStringLiteral(":/import")));
    _importDataFromTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                           Utility::SET_HEIGHT(45));
    _progressBar->setMinimum(0);
    _progressBar->setMaximum(100);
    _progressBar->setTextVisible(false);
    _progressBar->setFixedHeight(5);
    resetProgressBar();

    _outputDataGenerateFromFileLabel->setVisible(false);

    _textEdit->setPlaceholderText(tr("1- Generate the text\n2- Copy text or click on save button"));
    _textEdit->verticalScrollBar()->setStyleSheet(QStringLiteral("QScrollBar:vertical {width: 2px;}"));
    _textEdit->setTabChangesFocus(true);

    _generateTextButt->setIcon(QIcon(QStringLiteral(":/actualize")));
    _generateTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                     Utility::SET_HEIGHT(45));

    _clearTextButt->setIcon(QIcon(QStringLiteral(":/clear")));
    _clearTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREY)+
                                     Utility::SET_HEIGHT(45));

    _saveTextButt->setIcon(QIcon(QStringLiteral(":/save")));
    _saveTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREY)+
                                 Utility::SET_HEIGHT(45));

    _buttLayout->addWidget(_clearTextButt);
    _buttLayout->addWidget(_saveTextButt);
    _clearTextButt->setEnabled(false);
    _saveTextButt->setEnabled(false);

    _outputSaveFileLabel->setVisible(false);

    _mainLayout->addSpacing(20);
    _mainLayout->addWidget(_titleLabel);
    _mainLayout->addSpacing(20);
    _mainLayout->addWidget(_importDataFromTextButt);
    _mainLayout->addWidget(_progressBar);
    _mainLayout->addWidget(_outputDataGenerateFromFileLabel);
    _mainLayout->addSpacing(10);
    _mainLayout->addWidget(_textEdit);
    _mainLayout->addSpacing(10);
    _mainLayout->addWidget(_generateTextButt);
    _mainLayout->addLayout(_buttLayout);
    _mainLayout->addWidget(_outputSaveFileLabel);
    setLayout(_mainLayout);

    QObject::connect(_importDataFromTextButt,&QPushButton::clicked,this,&GenerateFileTab::importDatafromFile);
    QObject::connect(_textEdit,&QTextEdit::textChanged,this,&GenerateFileTab::textChangeEdit);
    QObject::connect(_generateTextButt,&QPushButton::clicked,this,&GenerateFileTab::generateTextEdit);
    QObject::connect(_clearTextButt,&QPushButton::clicked,this,&GenerateFileTab::clearTextEdit);
    QObject::connect(_saveTextButt,&QPushButton::clicked,this,&GenerateFileTab::saveTextInFile);
}

void GenerateFileTab::resetProgressBar(){
    _progressBar->setVisible(false);
    _progressBar->reset();
    _progressBar->setStyleSheet("QProgressBar{"+Utility::SET_BORDER_SIZE(0)+"}"+
                                "QProgressBar::chunk {"+Utility::SET_BACKGROUND_COLOR(COLOR_GREEN)+"}");
}
void GenerateFileTab::onTabSelected(){
    _outputSaveFileLabel->setVisible(false);
    _outputDataGenerateFromFileLabel->setVisible(false);
    resetProgressBar();
}

void GenerateFileTab::generateTextEdit(){
    _textEdit->clear();
    for(const auto& account: _facAccount.getAll()){
        _textEdit->append("@"+account->getName()+QLatin1String(":"));
        if(!account->getLogin().isEmpty())
            _textEdit->append(GFT_LOGIN+" "+account->getLogin());
        if(!account->getPassword().isEmpty())
            _textEdit->append(GFT_PASSWORD+" "+account->getPassword());
        if(account->getSeverityLvl()!=0)
            _textEdit->append(GFT_SEVERITY+" "+QString::number(account->getSeverityLvl()));
        if(!account->getDetails().isEmpty())
            _textEdit->append(GFT_DETAILS+" "+account->getDetails());
        _textEdit->append(QLatin1String(""));
    }
}

void GenerateFileTab::importDatafromFile(){
    _progressBar->setVisible(true);
    _progressBar->setStyleSheet("QProgressBar{"+Utility::SET_BORDER_SIZE(0)+"}"+
                                "QProgressBar::chunk {"+Utility::SET_BACKGROUND_COLOR(COLOR_GREEN)+"}");
    _outputDataGenerateFromFileLabel->setText(tr("Data from file imported"));
    _outputDataGenerateFromFileLabel->setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                                    Utility::SET_TEXT_COLOR(COLOR_GREEN));

    QString fileName{QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "./",
                                                  tr("Text (*.txt)"))};

    int nbrAccounts{getNumberAccountToImport(fileName)};
    int nbrAccountImported{0};

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QString _name;
        QString _Login;
        QString _password;
        QString _details;
        QString _saverity;
        bool hasName{false};
        bool detailsOngoing{false};

        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line{in.readLine()};

            if(!line.isEmpty()){
                if(line[0]=='@'){
                    ++nbrAccountImported;
                    _progressBar->setValue(nbrAccountImported*100/nbrAccounts);

                    if(hasName){
                        addNewAccount(QStringList()<< _name
                                      <<_Login
                                      <<_password
                                      <<_details
                                      <<_saverity);

                        _name.clear();
                        _Login.clear();
                        _details.clear();
                        _password.clear();
                        _saverity.clear();
                        hasName=false;
                        hasName=false;
                        detailsOngoing=false;
                    }

                    line.remove(0,1);
                    line.remove(line.size()-1,1);
                    _name=line;
                    hasName=true;
                }else if(hasName){
                    if(QStringRef(&line,0,6)==GFT_LOGIN){
                        _Login=QStringRef(&line,7,line.size()-7).toString();
                    }else if(QStringRef(&line,0,9)==GFT_PASSWORD){
                        _password=QStringRef(&line,10,line.size()-10).toString();
                    }else if(QStringRef(&line,0,9)==GFT_SEVERITY){
                        _saverity=QStringRef(&line,10,line.size()-10).toString();
                    }else if(QStringRef(&line,0,8)==GFT_DETAILS){
                        _details=QStringRef(&line,9,line.size()-9).toString();
                        detailsOngoing=true;
                    }else if(detailsOngoing){
                        _details=_details+"\n"+line;
                    }
                }

            }
        }
        if(hasName){
            addNewAccount(QStringList()<< _name
                          <<_Login
                          <<_password
                          <<_details
                          <<_saverity);
        }
        _progressBar->setValue(100);
        fireEventUpdate();
        _outputDataGenerateFromFileLabel->setVisible(true);
        inputFile.close();
    }
    resetProgressBar();
}

int GenerateFileTab::getNumberAccountToImport(const QString& iFileName){
    QFile inputFile(iFileName);
    int nbrAccount{0};
    if (inputFile.open(QIODevice::ReadOnly))
    {

        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line{in.readLine()};

            if(!line.isEmpty()){
                if(line[0]=='@'){
                    ++nbrAccount;
                }
            }
        }
        inputFile.close();
    }
    return nbrAccount;
}

void GenerateFileTab::clearTextEdit(){
    _textEdit->clear();
}

void GenerateFileTab::textChangeEdit(){
    if(_textEdit->toPlainText().isEmpty()){
        _clearTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREY)+
                                         Utility::SET_HEIGHT(45));
        _saveTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_GREY)+
                                     Utility::SET_HEIGHT(45));
        _clearTextButt->setEnabled(false);
        _saveTextButt->setEnabled(false);
    }else {
        _clearTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                         Utility::SET_HEIGHT(45));
        _saveTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                     Utility::SET_HEIGHT(45));
        _clearTextButt->setEnabled(true);
        _saveTextButt->setEnabled(true);
    }
}

void GenerateFileTab::addNewAccount(const QStringList& iAccount){
    if(_database.create(iAccount)==Utility::ERROR::no_error)
        _log.LOG_INFO("Account added from file: "+iAccount[0].toStdString());
    else{
        _progressBar->setStyleSheet("QProgressBar{"+Utility::SET_BORDER_SIZE(0)+"}"+
                                    "QProgressBar::chunk {"+Utility::SET_BACKGROUND_COLOR(COLOR_RED)+"}");
        _outputDataGenerateFromFileLabel->setText(tr("Some accounts weren't imported"));
        _outputDataGenerateFromFileLabel->setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                                        Utility::SET_TEXT_COLOR(COLOR_RED));
        _log.LOG_CRITICAL("Account failed to add from file: "+iAccount[0].toStdString());
    }
}

void GenerateFileTab::saveTextInFile(){
    if(!_textEdit->toPlainText().isEmpty()){
        QString pathFile{QFileDialog::getSaveFileName(this,
                                                      tr("Save password file"), "./", tr("Text Files (*.txt)"))};

        QStringList textList{_textEdit->toPlainText().split(QRegExp("[\n]"))};

        std::ofstream file{pathFile.toStdString()};

        if(file.is_open()){
            for(const auto& line: textList){
                file << line.toStdString() << std::endl;
            }
            file.close();
            _outputSaveFileLabel->setText(tr("File generated"));
            _outputSaveFileLabel->setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                                Utility::SET_TEXT_COLOR(COLOR_GREEN));
            _log.LOG_INFO("File generated");
        }else{
            _outputSaveFileLabel->setText(tr("File not created"));
            _outputSaveFileLabel->setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                                Utility::SET_TEXT_COLOR(COLOR_RED));
        }
    }else{
        _outputSaveFileLabel->setText(tr("The text is empty, generate the text first"));
        _outputSaveFileLabel->setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                            Utility::SET_TEXT_COLOR(COLOR_RED));
    }
    _outputSaveFileLabel->setVisible(true);
}
