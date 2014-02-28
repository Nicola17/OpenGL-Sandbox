#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

#include "glwidget.h"
#include "trianglesoupimporters.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _glWidget = new GLWidget;
    _logo = new QtLogo(this);

    _log.connectPTE(ui->_logPTE);
    _log.display("OpenGL Sandbox");
    ui->_openglLayout->addWidget(_glWidget);
    //QObject::connect(ui->_logoBtn,SIGNAL(toggled(bool)),this,SLOT(onLogoToggled(bool)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLogoToggled(bool v){
    if(v){
        ui->_logPTE->appendPlainText("Show logo\n");
        _glWidget->addDrawableObject(_logo);
        _glWidget->removeDrawableObject(&_triangleSoup);
        _glWidget->forceRepaint();
    }else{
        ui->_logPTE->appendPlainText("Hide logo\n");
        //_glWidget->setDrawableObject(nullptr);
        ui->_logPTE->appendPlainText("Load data\n");

        _glWidget->addDrawableObject(&_triangleSoup);

        IO::TriangleSoupImporters::read("F:\\Development\\OpenGLSandbox\\sources\\teapot.obj",_triangleSoup);
        ui->_logPTE->appendPlainText("done\n");
/*
        _triangleSoup.addTriangle(TriangleSoup::vector_type(0.5,0,0),
                                  TriangleSoup::vector_type(0,0,0.5),
                                  TriangleSoup::vector_type(0,0.5,0));
        _triangleSoup.addTriangle(TriangleSoup::vector_type(0,0,-0.5),
                                  TriangleSoup::vector_type(0.5,0,0),
                                  TriangleSoup::vector_type(0,0.5,0));
*/
        _glWidget->forceRepaint();
    }
}
