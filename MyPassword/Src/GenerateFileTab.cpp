#include "GenerateFileTab.h"

#include "Account.h"
#include "Interface/ILog.h"
#include "Utility.h"

#include <QScrollBar>
#include <QFileDialog>
#include <QString>

#include <fstream>

GenerateFileTab::GenerateFileTab(FacAccount& iFacAccount, ILog& iLog):
    _facAccount{iFacAccount},
    _log{iLog}
{
    setMinimumWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QTEXTEDIT());

    _titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel->setStyleSheet(Utility::SET_TEXT_SIZE(40)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));

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
    _mainLayout->addWidget(_textEdit);
    _mainLayout->addSpacing(10);
    _mainLayout->addLayout(_buttLayout);
    _mainLayout->addWidget(_outputSaveFileLabel);
    setLayout(_mainLayout);

    QObject::connect(_generateTextButt,&QPushButton::clicked,this,&GenerateFileTab::fillTextEdit);
    QObject::connect(_saveTextButt,&QPushButton::clicked,this,&GenerateFileTab::saveTextInFile);
}

void GenerateFileTab::onTabSelected(){
    _outputSaveFileLabel->setVisible(false);
}

void GenerateFileTab::fillTextEdit(){
    _textEdit->clear();
    for(const auto& account: _facAccount.getAll()){
        _textEdit->append(account->getName()+QLatin1String(":"));
        _textEdit->append(tr("Name: ")+account->getLogin());
        _textEdit->append(tr("Details : ")+account->getDetails());
        _textEdit->append(QLatin1String(""));
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
