#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _glWidget = new GLWidget;
    ui->_logPTE->appendPlainText("Hello world\n");
    ui->_openglLayout->addWidget(_glWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
