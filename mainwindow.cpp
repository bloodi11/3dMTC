#include "engine.h"
#include <memory>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    std::unique_ptr<WorkSpace> workSpace = std::make_unique<WorkSpace>(path);
}
