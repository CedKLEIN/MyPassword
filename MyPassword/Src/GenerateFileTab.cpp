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

    _textEdit->setPlaceholderText(tr("1- Generate the text\n2- Copy text or click on save button"));
    _textEdit->verticalScrollBar()->setStyleSheet(QStringLiteral("QScrollBar:vertical {width: 2px;}"));
    _textEdit->setTabChangesFocus(true);

    _generateTextButt->setIcon(QIcon(QStringLiteral(":/actualize")));
    _generateTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                     Utility::SET_HEIGHT(45));

    _saveTextButt->setIcon(QIcon(QStringLiteral(":/save")));
    _saveTextButt->setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                 Utility::SET_HEIGHT(45));

    _buttLayout->addWidget(_generateTextButt);
    _buttLayout->addWidget(_saveTextButt);

    _outputSaveFileLabel->setVisible(false);

    _mainLayout->addSpacing(20);
    _mainLayout->addWidget(_titleLabel);
    _mainLayout->addSpacing(20);
    _mainLayout->addWidget(_importDataFromTextButt);
    _mainLayout->addSpacing(10);
    _mainLayout->addWidget(_textEdit);
    _mainLayout->addSpacing(10);
    _mainLayout->addLayout(_buttLayout);
    _mainLayout->addWidget(_outputSaveFileLabel);
    setLayout(_mainLayout);

    QObject::connect(_importDataFromTextButt,&QPushButton::clicked,this,&GenerateFileTab::importDatafromFile);
    QObject::connect(_generateTextButt,&QPushButton::clicked,this,&GenerateFileTab::generateTextEdit);
    QObject::connect(_saveTextButt,&QPushButton::clicked,this,&GenerateFileTab::saveTextInFile);
}

void GenerateFileTab::onTabSelected(){
    _outputSaveFileLabel->setVisible(false);
}

void GenerateFileTab::generateTextEdit(){
    _textEdit->clear();
    for(const auto& account: _facAccount.getAll()){
        _textEdit->append("@"+account->getName()+QLatin1String(":"));
        if(!account->getLogin().isEmpty())
            _textEdit->append(tr("Login: ")+account->getLogin());
        if(!account->getDetails().isEmpty())
            _textEdit->append(tr("Details: ")+account->getDetails());
        _textEdit->append(QLatin1String(""));
    }
}

void GenerateFileTab::importDatafromFile(){
    QString fileName{QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "./",
                                                  tr("Text (*.txt)"))};

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QString _name;
        QString _Login;
        QString _details;
        bool hasName{false};
        bool detailsOngoing{false};

        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line{in.readLine()};

            if(!line.isEmpty()){
                if(line[0]=='@'){
                    if(hasName){
                        addNewAccount(QStringList()<< _name
                                      <<_Login
                                      <<""
                                      <<_details
                                      <<"");

                        _name.clear();
                        _Login.clear();
                        _details.clear();
                        hasName=false;
                        detailsOngoing=false;
                    }

                    line.remove(0,1);
                    line.remove(line.size()-1,1);
                    _name=line;
                    hasName=true;
                }else if(hasName){
                    if(QStringRef(&line,0,6)=="Login:"){
                        _Login=QStringRef(&line,7,line.size()-7).toString();
                    }else if(QStringRef(&line,0,8)=="Details:"){
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
                          <<""
                          <<_details
                          <<"");
        }
        fireEventUpdate();
        inputFile.close();
    }
}

void GenerateFileTab::addNewAccount(const QStringList& iAccount){
    if(_database.create(iAccount)==Utility::ERROR::no_error)
        _log.LOG_INFO("Account added from file: "+iAccount[0].toStdString());
    else
        _log.LOG_CRITICAL("Account failed to add from file: "+iAccount[0].toStdString());
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
