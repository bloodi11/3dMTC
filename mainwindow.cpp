#include "engine.h"
#include <memory>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
            tr("Load 3d model to workspace"), "",
            tr("Object (*.obj);"));
    ui->pathLineEdit->setText(path);
    std::shared_ptr<WorkSpace> workSpace = std::make_shared<WorkSpace>(path);

    ui->myGLWidget->workspace = workSpace;

}

