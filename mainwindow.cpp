#include "engine.h"
#include <memory>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <iostream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect( ui->zoomPlus_button, SIGNAL( clicked() ), ui->myGLWidget, SLOT( scalePlus() ) );
    connect( ui->zoomMinus_button, SIGNAL( clicked() ), ui->myGLWidget, SLOT( scaleMinus() ) );

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_button_setPath_clicked(){
    QString path = QFileDialog::getOpenFileName(this,
            tr("Load 3d model to workspace"), "",
            tr("Object (*.obj);"));
    ui->pathLineEdit->setText(path);
    ui->textEdit->clear();

    auto workSpace = std::make_shared<WorkSpace>(path);

    ui->model_paramX->setText(QString::number(workSpace->_model.getXDistance()));
    ui->model_paramY->setText(QString::number(workSpace->_model.getYDistance()));
    ui->model_paramZ->setText(QString::number(workSpace->_model.getZDistance()));

    workSpace->_material.setMaterialParamX(ui->material_paramX->text().toFloat());
    workSpace->_material.setMaterialParamY(ui->material_paramY->text().toFloat());
    workSpace->_material.setMaterialParamZ(ui->material_paramZ->text().toFloat());

    workSpace->_material.setStep(ui->lineEdit_step->text().toFloat());

    ui->myGLWidget->workspace = workSpace;
}



void MainWindow::on_convert_button_clicked()
{
    if(ui->myGLWidget->workspace == nullptr){ /* DO NOTHING */ }
    else if(ui->myGLWidget->workspace != nullptr){
    auto process = std::make_unique<Process>();
    process->_workspace = ui->myGLWidget->workspace;
    process->parseToGCode(process->_workspace);
    ui->textEdit->append(QString::fromStdString(process->code));
    }
}

void MainWindow::on_export_button_clicked()
{

}
