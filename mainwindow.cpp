#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QSettings>

#include "glwidget.h"
#include "trianglesoupimporters.h"
#include "surface_mesh/Surface_mesh.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _glWidget = new GLWidget;
    ui->_openglLayout->addWidget(_glWidget);

    _log.connectPTE(ui->_logPTE);
    _logGlWidget.connectPTE(ui->_glWidgetLogPTE);
    _log.display("OpenGL Sandbox");
    _logGlWidget.display("GLWidget log");
    _glWidget->_log = &_logGlWidget;

    signalConnection();
    readSettings();
}

MainWindow::~MainWindow()
{
    writeSettings();
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
    QObject::connect(ui->_clearLogBtn,SIGNAL(clicked()),this,SLOT(onShowAxes(bool)));

    QObject::connect(ui->_bgColorBtn,SIGNAL(clicked()),this,SLOT(onChangeBGColor()));
    QObject::connect(ui->_verboseChBx,SIGNAL(toggled(bool)),this,SLOT(onChangeVerbosity(bool)));
    QObject::connect(ui->_reloadDataBtn,SIGNAL(clicked()),this,SLOT(onLoadData()));
    QObject::connect(ui->_changeDefaultDataDirBtn,SIGNAL(clicked()),this,SLOT(onChangeDefaultDataDir()));

    QObject::connect(ui->_showAxesChkBx,SIGNAL(toggled(bool)),this,SLOT(onShowAxes(bool)));
    QObject::connect(ui->_axesLengthDSpBx,SIGNAL(valueChanged(double)),this,SLOT(onChangeAxesLength(double)));

    QObject::connect(ui->_showCameraCenterChkBx,SIGNAL(toggled(bool)),this,SLOT(onShowCameraCenter(bool)));
    QObject::connect(ui->_cameraCenterSizeDSpBx,SIGNAL(valueChanged(double)),this,SLOT(onChangeCameraCenterSize(double)));
    QObject::connect(ui->_cameraMovementSpeedDSpBx,SIGNAL(valueChanged(double)),this,SLOT(onChangeCameraMovementSpeed(double)));
    QObject::connect(ui->_cameraRotationSpeedDSpBx,SIGNAL(valueChanged(double)),this,SLOT(onChangeCameraRotationSpeed(double)));

    QObject::connect(ui->_resetCameraBtn,SIGNAL(clicked()),_glWidget,SLOT(onResetCameraPosition()));
}

void MainWindow::readSettings(){
    _log.display("Read settings");
    QSettings settings("Nicola17","OpenGL Sandbox");
    ui->_defaultDataDirLE->setText(settings.value("Default dir","").toString());
}
void MainWindow::writeSettings(){
    _log.display("Write settings");
    QSettings settings("Nicola17","OpenGL Sandbox");
    settings.setValue("Default dir",ui->_defaultDataDirLE->text());
}

void MainWindow::onLoadData(){
    _log.display("Load data");
    QString defaultDir = ui->_defaultDataDirLE->text();
    _bullseyeTS = new QtLogo(this);

    try{
        IO::TriangleSoupImporters::readObj(defaultDir+"\\teapot.obj",_teapotTS,1/30.,&_log);
        _teapotTS.initialize();
    }
    catch(std::runtime_error& ex){SECURE_LOG_VAL(&_log,"Runtime error",ex.what())}
    catch(std::logic_error& ex){SECURE_LOG_VAL(&_log,"Logic error",ex.what())}
    try{
        IO::TriangleSoupImporters::readObj(defaultDir+"\\bunny.obj",_bunnyTS,10,&_log);
        _bunnyTS.initialize();
    }
    catch(std::runtime_error& ex){SECURE_LOG_VAL(&_log,"Runtime error",ex.what())}
    catch(std::logic_error& ex){SECURE_LOG_VAL(&_log,"Logic error",ex.what())}
    try{
        IO::TriangleSoupImporters::readObj(defaultDir+"\\dragon.obj",_dragonTS,10,&_log);
        _dragonTS.initialize();
    }
    catch(std::runtime_error& ex){SECURE_LOG_VAL(&_log,"Runtime error",ex.what())}
    catch(std::logic_error& ex){SECURE_LOG_VAL(&_log,"Logic error",ex.what())}
    try{
        IO::TriangleSoupImporters::readObj(defaultDir+"\\buddha.obj",_buddhaTS,10,&_log);
        _buddhaTS.initialize();
    }
    catch(std::runtime_error& ex){SECURE_LOG_VAL(&_log,"Runtime error",ex.what())}
    catch(std::logic_error& ex){SECURE_LOG_VAL(&_log,"Logic error",ex.what())}
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

void MainWindow::onChangeBGColor(){
    try{
        _log.display("Change BG color");
        _bgColor = QColorDialog::getColor(_bgColor, this);
        _glWidget->setBackgroundColor(_bgColor);
        _glWidget->forceRepaint();
    }
    catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
    catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
}

 void MainWindow::onChangeVerbosity(bool v){
     try{
         _log.display("Change verbosity");
         _glWidget->_verbose = v;
         _verbose = v;
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }

 void MainWindow::onChangeDefaultDataDir(){
     try{
        _log.display("Change default dir");
        QString defaultDir = QFileDialog::getExistingDirectory(this,"Open default directory",ui->_defaultDataDirLE->text());
        ui->_defaultDataDirLE->setText(defaultDir);
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }

 void MainWindow::keyPressEvent(QKeyEvent *e){
     if (e->key() == Qt::Key_Escape){
         close();
     }else if (e->key() == Qt::Key_W){
        SECURE_LOG_VERBOSE(&_log,"Move ahead");
        _glWidget->moveCamera(QVector3D(0,0,1));
        _glWidget->forceRepaint();
     }else if (e->key() == Qt::Key_S){
        SECURE_LOG_VERBOSE(&_log,"Move backwards");
        _glWidget->moveCamera(QVector3D(0,0,-1));
        _glWidget->forceRepaint();
     }else if (e->key() == Qt::Key_D){
        SECURE_LOG_VERBOSE(&_log,"Shift right");
        _glWidget->moveCamera(QVector3D(1,0,0));
        _glWidget->forceRepaint();
     }else if (e->key() == Qt::Key_A){
        SECURE_LOG_VERBOSE(&_log,"Shift left");
        _glWidget->moveCamera(QVector3D(-1,0,0));
        _glWidget->forceRepaint();
     }else if (e->key() == Qt::Key_R){
        SECURE_LOG_VERBOSE(&_log,"Shift up");
        _glWidget->moveCamera(QVector3D(0,1,0));
        _glWidget->forceRepaint();
     }else if (e->key() == Qt::Key_F){
        SECURE_LOG_VERBOSE(&_log,"Shift down");
        _glWidget->moveCamera(QVector3D(0,-1,0));
        _glWidget->forceRepaint();
     }else
         QWidget::keyPressEvent(e);
 }

 void MainWindow::onChangeCameraMovementSpeed(double speed){
     try{
        SECURE_LOG_VAL_VERBOSE(&_log,"Camera speed", speed);
        _glWidget->cameraSpeed() = speed;
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }
 void MainWindow::onChangeCameraRotationSpeed(double speed){
     try{
        SECURE_LOG_VAL_VERBOSE(&_log,"Camera rotation speed", speed);
        _glWidget->cameraRotationSpeed() = speed;
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }
 void MainWindow::onChangeCameraCenterSize(double size){
     try{
        SECURE_LOG_VAL_VERBOSE(&_log,"Camera center size", size);
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }
 void MainWindow::onShowCameraCenter(bool v){
     try{
         SECURE_LOG_VAL_VERBOSE(&_log,"Show camera center", (v?"ON":"OFF"));
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }

 void MainWindow::onChangeAxesLength(double length){
     try{
         SECURE_LOG_VAL_VERBOSE(&_log,"Axes length", length);
         _glWidget->axesLength() = length;
         _glWidget->forceRepaint();
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }
 void MainWindow::onShowAxes(bool v){
     try{
         SECURE_LOG_VAL_VERBOSE(&_log,"Show axes", (v?"ON":"OFF"));
         _glWidget->showAxes() = v;
         _glWidget->forceRepaint();
     }
     catch(std::runtime_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
     catch(std::logic_error& ex){QMessageBox::critical(this,tr("Critical error"),ex.what());}
 }
