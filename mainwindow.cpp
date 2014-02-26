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
    _logo = new QtLogo(this);

    ui->_logPTE->appendPlainText("Hello world\n");
    ui->_openglLayout->addWidget(_glWidget);
    QObject::connect(ui->_logoBtn,SIGNAL(toggled(bool)),this,SLOT(onLogoToggled(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLogoToggled(bool v){
    if(v){
        ui->_logPTE->appendPlainText("Show logo\n");
        _glWidget->setDrawableObject(_logo);
        _glWidget->forceRepaint();
    }else{
        ui->_logPTE->appendPlainText("Hide logo\n");
        //_glWidget->setDrawableObject(nullptr);
        _glWidget->setDrawableObject(&_triangleSoup);
        _triangleSoup.addTriangle(TriangleSoup::vector_type(0.5,0,0),
                                  TriangleSoup::vector_type(0,0,0.5),
                                  TriangleSoup::vector_type(0,0.5,0));
        _triangleSoup.addTriangle(TriangleSoup::vector_type(0,0,-0.5),
                                  TriangleSoup::vector_type(0.5,0,0),
                                  TriangleSoup::vector_type(0,0.5,0));
        _glWidget->forceRepaint();
    }
}
