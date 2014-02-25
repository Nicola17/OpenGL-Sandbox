#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtlogo.h"

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
    GLWidget*       _glWidget;
    QtLogo*         _logo;
};

#endif // MAINWINDOW_H
