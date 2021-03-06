#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "Drawables/qtlogo.h"
#include "Drawables/trianglesoup.h"
#include "Utils/ptelog.h"
#include "Drawables/pointdrw.h"
#include "Drawables/linedrw.h"
#include "Drawables/drawabletrimesh.h"



class GLWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void signalConnection();
    void readSettings();
    void writeSettings();

public slots:
    void onLoadData();
    void onBullseyeToggled(bool v);
    void onTeapotToggled(bool v);
    void onDragonToggled(bool v);
    void onBuddhaToggled(bool v);
    void onBunnyToggled(bool v);
    void onUserTriangleSoupToggled(bool v);

    void onBunnyPCToggled(bool v);
    void onUserPCToggled(bool v);

    void onClearLog();
    void onChangeBGColor();
    void onChangeVerbosity(bool v);
    void onChangeDefaultDataDir();

    void onChangeCameraMovementSpeed(double speed);
    void onChangeCameraRotationSpeed(double speed);
    void onChangeCameraCenterSize(double size);
    void onShowCameraCenter(bool v);

    void onChangeAxesLength(double length);
    void onShowAxes(bool v);



protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow* ui;

    PTELog          _log;
    PTELog          _logGlWidget;
    GLWidget*       _glWidget;

    QtLogo*         _bullseyeTS;
    TriangleSoup    _buddhaTS;
    TriangleSoup    _bunnyTS;
    TriangleSoup    _dragonTS;
    TriangleSoup    _teapotTS;
    TriangleSoup    _userTS;

    DrawableTriMesh _teapotMesh;

    QColor          _bgColor;
    bool            _verbose;

};

#endif // MAINWINDOW_H
