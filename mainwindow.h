#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Drawables/qtlogo.h"
#include "Drawables/trianglesoup.h"
#include "Utils/ptelog.h"

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

public slots:
    void onLogoToggled(bool v);

private:
    Ui::MainWindow* ui;

    PTELog          _log;
    GLWidget*       _glWidget;
    QtLogo*         _logo;
    TriangleSoup    _triangleSoup;
};

#endif // MAINWINDOW_H
