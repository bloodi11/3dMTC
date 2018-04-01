#include "engine.h"
#include <memory>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect( ui->zoomPlus_button, SIGNAL( clicked() ), ui->myGLWidget, SLOT( scalePlus() ) );
    connect( ui->zoomMinus_button, SIGNAL( clicked() ), ui->myGLWidget, SLOT( scaleMinus() ) );

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_button_setPath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
            tr("Load 3d model to workspace"), "",
            tr("Object (*.obj);"));
    ui->pathLineEdit->setText(path);
    auto workSpace = std::make_unique<WorkSpace>(path);

    ui->myGLWidget->workspace = std::move(workSpace);
}

