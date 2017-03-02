#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//QGis Includes
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>

#include <QtGui>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QgsMapCanvas * mpMapCanvas;
        QVBoxLayout  * mpLayout;
        QToolBar * mpMapToolBar;
        QgsMapTool * mpPanTool;
        QgsMapTool * mpZoomInTool;
        QgsMapTool * mpZoomOutTool;

public slots:
      void zoomInMode();
      void zoomOutMode();
      void panMode();
      void addLayer();
};

#endif // MAINWINDOW_H
