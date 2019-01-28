#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFont>
//#include <Windows.h>
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonInput_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this,tr("open directory"),"/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    ui->lineEditInput->setText(filePath);
    ui->lineEditInput->setEnabled(false);
}

void MainWindow::on_pushButtonOutput_clicked()
{
    QString outPath = QFileDialog::getExistingDirectory(this,tr("open directory"),"/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    ui->lineEditOutput->setText(outPath);
    ui->lineEditOutput->setEnabled(false);
//    ui->lineEditOutput->update();
    QString inputPath = ui->lineEditInput->text();
    QFileInfoList tempFileInfoList = getFileList(inputPath);
    for(int i=0; i<tempFileInfoList.size(); i++)
    {
        QFileInfo tempFileInfo = tempFileInfoList.at(i);
        QString tempSuffix = tempFileInfo.completeSuffix();
        if(tempSuffix.size() < 1)
        {
            tempSuffix = "fileNoSuffix";
        }
        QString tempOutPath = outPath + "/" + tempSuffix;
        QDir tmpDir(tempOutPath);
        if(!tmpDir.exists())
        {
            tmpDir.mkpath(tempOutPath);
        }
        QString tmpFileName = tempFileInfo.absoluteFilePath();
        QString fileName = tempFileInfo.fileName();
        tempOutPath = tempOutPath+"/"+fileName;
//        qDebug() << tmpFileName << endl;
        QFile::copy(tmpFileName,tempOutPath);
        QTableWidgetItem *suffixItem = new QTableWidgetItem();
        suffixItem->setText(tempSuffix);
        QTableWidgetItem *outpathItem = new QTableWidgetItem();
        outpathItem->setText(tempOutPath);
        outpathItem->setToolTip(tempOutPath);
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,suffixItem);
        ui->tableWidget->setItem(i,1,outpathItem);
        ui->tableWidget->setAutoScroll(true);
        ui->statusBar->showMessage("choose data....");

        QFont font("Times",18,QFont::Black);
        ui->statusBar->setFont(font);
    }
    QMessageBox::information(NULL,"title","choose over");
    ui->statusBar->showMessage("choose over");
}

QFileInfoList MainWindow::getFileList(QString path)
{
    QDir dir(path);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i=0; i<folderList.size(); i++)
    {
        QString name = folderList.at(i).absoluteFilePath();
        QFileInfoList chileFileList = getFileList(name);
        fileList.append(chileFileList);
    }
    return fileList;
}
