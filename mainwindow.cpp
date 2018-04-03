#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "C:/");
}

void MainWindow::deleteDir(QDir dir){
    foreach(QFileInfo file, dir.entryInfoList()){
        if(!dir.absolutePath().contains(file.absoluteFilePath())){
            if(file.isDir()){
                QDir dirToOpen(file.absoluteFilePath());
                deleteDir(dirToOpen);
            }else{
                if(file.fileName().contains("(1)")){
                    QFile fileToDelete(file.absoluteFilePath());
                    fileToDelete.remove();
                    ui->textBrowser->append(file.absoluteFilePath());
                }
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(dir.isEmpty()){
        QMessageBox::information(this, "Error", "Select a directory first.");
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", "Every file containing (1) will be deleted, are you sure you want to continue?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            deleteDir(dir);
        }
    }
}
