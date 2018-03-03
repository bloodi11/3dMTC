#include "engine.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    WorkSpace workSpace(ui->pathLineEdit->text());
}

MainWindow::~MainWindow() {
    delete ui;
}
