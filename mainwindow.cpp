#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rabin.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString fileBytes(QString tFileName){
    QFile file(tFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return "";
    }
    QByteArray fileData = file.read(20);
    QString text;
    for (int i = 0;i < fileData.size(); ++i){
        text += QString::number(static_cast<uchar>(fileData.at(i))) + " ";
    }
    file.close();
    return text;
}


QString fileStrings(QString tFileName){
    QFile file(tFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return "";
    }

    QTextStream in(&file);
    QStringList words;
    QString text;

    int spaceCount = 0;
    while (!in.atEnd() && spaceCount < 20) {
        QString line = in.readLine();
        QStringList lineWords = line.split(" ", Qt::SkipEmptyParts);
        for (const QString& word : lineWords) {
            words.append(word);
            spaceCount++;
                if (spaceCount > 20)
                    break;
            }
    }
    for (int i = 0;i<words.size();++i){
        text = text + words[i] + " ";
    }

    file.close();
    return text;
}


void MainWindow::on_pushButtonEncode_clicked()
{
    ui->label->setText("");
    if(rabi.processValues(ui->lineEditP->text(), ui->lineEditQ->text(), ui->lineEditB->text())){
        if (FileName!=""){
            rabi.encode(FileName);
            ui->textEdit->setText(fileBytes(FileName));
            ui->textEdit_2->setText(fileStrings("temp.txt"));
            ui->label->setText("Operation Completed");
        }
        else{
            ui->label->setText("Choose File");
        }
    }else{
        ui->label->setText("Error of p or q or b");
    }

}


void MainWindow::on_openFileButton_clicked()
{
    FileName = QFileDialog::getOpenFileName();
    ui->labelFile->setText(FileName);

}


void MainWindow::on_pushButtonDecode_clicked()
{
    if(rabi.processValues(ui->lineEditP->text(), ui->lineEditQ->text(), ui->lineEditB->text())){
        if (FileName!=""){
            rabi.decode(FileName);
            ui->textEdit->setText(fileStrings(FileName));
            ui->textEdit_2->setText(fileBytes("result.txt"));
            ui->label->setText("Operation Completed");
        }else{
            ui->label->setText("Choose File");
        }
    }else{
        ui->label->setText("Error of p or q or b");
    }

}

