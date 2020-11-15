#include "GenerateFileTab.h"

#include "Account.h"
#include "Utility.h"

#include <QDebug>
#include <QScrollBar>
#include <QFileDialog>

#include <fstream>

GenerateFileTab::GenerateFileTab(FacAccount& iFacAccount):
    _facAccount(iFacAccount)
{
    setFixedWidth(SIZE_WINDOW_HORIZONTAL);
    setStyleSheet(Utility::GET_STYLE_QPUSHBUTTON()+
                  Utility::GET_STYLE_QTEXTEDIT());

    _titleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    _titleLabel.setStyleSheet(Utility::SET_TEXT_SIZE(35,BOLD)+
                              Utility::SET_TEXT_COLOR(COLOR_LIGHT));

    _generateTextButt.setIcon(QIcon(":/actualize"));
    _generateTextButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                    Utility::SET_HEIGHT(45));
    _saveTextButt.setIcon(QIcon(":/save"));
    _saveTextButt.setStyleSheet(Utility::SET_BACKGROUND_COLOR(COLOR_BLUE)+
                                Utility::SET_HEIGHT(45));

    _textEdit.setPlaceholderText("1- Generate the text\n2- Copy text or click on save button");
    _textEdit.verticalScrollBar()->setStyleSheet("QScrollBar:vertical {width: 2px;}");

    _buttLayout.addWidget(&_generateTextButt);
    _buttLayout.addWidget(&_saveTextButt);

    _outputSaveFileLabel.setVisible(false);

    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_titleLabel);
    _mainLayout.addSpacing(20);
    _mainLayout.addWidget(&_textEdit);
    _mainLayout.addSpacing(10);
    _mainLayout.addLayout(&_buttLayout);
    _mainLayout.addWidget(&_outputSaveFileLabel);
    setLayout(&_mainLayout);

    QObject::connect(&_generateTextButt,&QPushButton::clicked,this,&GenerateFileTab::fillTextEdit);
    QObject::connect(&_saveTextButt,&QPushButton::clicked,this,&GenerateFileTab::saveTextInFile);
}

void GenerateFileTab::onTabSelected(){
    _outputSaveFileLabel.setVisible(false);
}

void GenerateFileTab::fillTextEdit(){
    _textEdit.clear();
    for(const auto& account: _facAccount.getAll()){
        _textEdit.append(account->getName()+":");
        _textEdit.append("Name: "+account->getLogin());
        _textEdit.append("Details : "+account->getDetails());
        _textEdit.append("");
    }
}

void GenerateFileTab::saveTextInFile(){
    if(!_textEdit.toPlainText().isEmpty()){
        QString pathFile{QFileDialog::getSaveFileName(this,
                                                      tr("Save password file"), "./", tr("Text Files (*.txt)"))};

        QStringList textList{_textEdit.toPlainText().split(QRegExp("[\n]"))};

        std::ofstream file{pathFile.toStdString()};

        if(file.is_open()){
            for(const auto& line: textList){
                file << line.toStdString() << std::endl;
            }
            file.close();
            _outputSaveFileLabel.setText("File generated");
            _outputSaveFileLabel.setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                               Utility::SET_TEXT_COLOR(COLOR_GREEN));
        }else{
            _outputSaveFileLabel.setText("File not created.");
            _outputSaveFileLabel.setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                               Utility::SET_TEXT_COLOR(COLOR_RED));
        }
    }else{
        _outputSaveFileLabel.setText("The text is empty, generate the file first.");
        _outputSaveFileLabel.setStyleSheet(Utility::SET_TEXT_SIZE(TEXT_STANDARD_SIZE,ITALIC)+
                                           Utility::SET_TEXT_COLOR(COLOR_RED));
    }
    _outputSaveFileLabel.setVisible(true);
}
