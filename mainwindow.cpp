#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>

#include "glwidget.h"
#include "trianglesoupimporters.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _glWidget = new GLWidget;

    _log.connectPTE(ui->_logPTE);
    _log.display("OpenGL Sandbox");
    ui->_openglLayout->addWidget(_glWidget);

    signalConnection();
    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signalConnection(){
    QObject::connect(ui->_bullseyeChBx,SIGNAL(toggled(bool)),this,SLOT(onBullseyeToggled(bool)));
    QObject::connect(ui->_teapotChBx,SIGNAL(toggled(bool)),this,SLOT(onTeapotToggled(bool)));
    QObject::connect(ui->_dragonChBx,SIGNAL(toggled(bool)),this,SLOT(onDragonToggled(bool)));
    QObject::connect(ui->_buddhaChBx,SIGNAL(toggled(bool)),this,SLOT(onBuddhaToggled(bool)));
    QObject::connect(ui->_bunnyChBx,SIGNAL(toggled(bool)),this,SLOT(onBunnyToggled(bool)));
    QObject::connect(ui->_bunnyPCChBx,SIGNAL(toggled(bool)),this,SLOT(onBunnyPCToggled(bool)));
    QObject::connect(ui->_userChBx,SIGNAL(toggled(bool)),this,SLOT(onUserTriangleSoupToggled(bool)));
    QObject::connect(ui->_userPCChBx,SIGNAL(toggled(bool)),this,SLOT(onUserPCToggled(bool)));
    QObject::connect(ui->_clearLogBtn,SIGNAL(clicked()),this,SLOT(onClearLog()));
}

/*
void MainWindow::onTeapotToggled(bool v){
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

        _triangleSoup.addTriangle(TriangleSoup::vector_type(0.5,0,0),
                                  TriangleSoup::vector_type(0,0,0.5),
                                  TriangleSoup::vector_type(0,0.5,0));
        _triangleSoup.addTriangle(TriangleSoup::vector_type(0,0,-0.5),
                                  TriangleSoup::vector_type(0.5,0,0),
                                  TriangleSoup::vector_type(0,0.5,0));

        _glWidget->forceRepaint();
    }
}
*/

void MainWindow::loadData(){
    _bullseyeTS = new QtLogo(this);

    IO::TriangleSoupImporters::read("F:\\Development\\OpenGLSandbox\\sources\\teapot.obj",_teapotTS);
}

void MainWindow::onBullseyeToggled(bool v){
    try{
        if(v){
            _log.display("Show bullseye");
            _glWidget->addDrawableObject(_bullseyeTS);
            _glWidget->forceRepaint();
        }else{
            _log.display("Hide bullseye");
            _glWidget->removeDrawableObject(_bullseyeTS);
            _glWidget->forceRepaint();
        }
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}
void MainWindow::onTeapotToggled(bool v){
    try{
        if(v){
            _log.display("Show teapot");
            _glWidget->addDrawableObject(&_teapotTS);
            _glWidget->forceRepaint();
        }else{
            _log.display("Hide teapot");
            _glWidget->removeDrawableObject(&_teapotTS);
            _glWidget->forceRepaint();
        }
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}
void MainWindow::onDragonToggled(bool v){
    try{
        if(v){
            _log.display("Show dragon");
            _glWidget->addDrawableObject(&_dragonTS);
            _glWidget->forceRepaint();
        }else{
            _log.display("Hide dragon");
            _glWidget->removeDrawableObject(&_dragonTS);
            _glWidget->forceRepaint();
        }
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}
void MainWindow::onBuddhaToggled(bool v){
    try{
        if(v){
            _log.display("Show Buddha");
            _glWidget->addDrawableObject(&_buddhaTS);
            _glWidget->forceRepaint();
        }else{
            _log.display("Hide Buddha");
            _glWidget->removeDrawableObject(&_buddhaTS);
            _glWidget->forceRepaint();
        }
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}
void MainWindow::onBunnyToggled(bool v){
    try{
        if(v){
            _log.display("Show Stanford bunny");
            _glWidget->addDrawableObject(&_bunnyTS);
            _glWidget->forceRepaint();
        }else{
            _log.display("Hide Stanford bunny");
            _glWidget->removeDrawableObject(&_bunnyTS);
            _glWidget->forceRepaint();
        }
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}
void MainWindow::onUserTriangleSoupToggled(bool v){
    try{
        if(v){
            _log.display("Show user defined triangle soup");
            _glWidget->addDrawableObject(&_userTS);
            _glWidget->forceRepaint();
        }else{
            _log.display("Hide user defined triangle soup");
            _glWidget->removeDrawableObject(&_userTS);
            _glWidget->forceRepaint();
        }
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}
void MainWindow::onBunnyPCToggled(bool v){}
void MainWindow::onUserPCToggled(bool v){}

void MainWindow::onClearLog(){
    _log.clear();
}
