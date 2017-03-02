#include "mainwindow.h"
#include "ui_mainwindow.h"

// QGIS Includes
//
#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgssinglesymbolrendererv2.h>
#include <qgsmaplayerregistry.h>
#include <qgsvectorlayer.h>
#include <qgsmapcanvas.h>
//
// QGIS Map tools
//
#include "qgsmaptoolpan.h"
#include "qgsmaptoolzoom.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString myPluginsDir        = "/urs/lib/qgis";
    QgsProviderRegistry::instance(myPluginsDir);

    mpMapCanvas= new QgsMapCanvas(0, 0);
      mpMapCanvas->enableAntiAliasing(true);
      mpMapCanvas->useImageToRender(false);
      mpMapCanvas->setCanvasColor(QColor(255, 255, 255));
      mpMapCanvas->freeze(false);
      mpMapCanvas->setVisible(true);
      mpMapCanvas->refresh();
      mpMapCanvas->show();

      // Lay our widgets out in the main window
      mpLayout = new QVBoxLayout(ui->frameMap);
      mpLayout->addWidget(mpMapCanvas);

      //create the action behaviours
      connect(ui->mpActionPan, SIGNAL(triggered()), this, SLOT(panMode()));
      connect(ui->mpActionZoomIn, SIGNAL(triggered()), this, SLOT(zoomInMode()));
      connect(ui->mpActionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOutMode()));
      connect(ui->mpActionAddLayer, SIGNAL(triggered()), this, SLOT(addLayer()));

      //create a little toolbar
      mpMapToolBar = addToolBar(tr("File"));
      mpMapToolBar->addAction(ui->mpActionAddLayer);
      mpMapToolBar->addAction(ui->mpActionZoomIn);
      mpMapToolBar->addAction(ui->mpActionZoomOut);
      mpMapToolBar->addAction(ui->mpActionPan);

      //create the maptools
      mpPanTool = new QgsMapToolPan(mpMapCanvas);
      mpPanTool->setAction(ui->mpActionPan);
      mpZoomInTool = new QgsMapToolZoom(mpMapCanvas, false); // false = in
      mpZoomInTool->setAction(ui->mpActionZoomIn);
      mpZoomOutTool = new QgsMapToolZoom(mpMapCanvas, true ); //true = out
      mpZoomOutTool->setAction(ui->mpActionZoomOut);

}

MainWindow::~MainWindow()
{
    delete ui;

    delete mpZoomInTool;
      delete mpZoomOutTool;
      delete mpPanTool;
      delete mpMapToolBar;
      delete mpMapCanvas;
      delete mpLayout;
}


void MainWindow::panMode()
{
  mpMapCanvas->setMapTool(mpPanTool);

}
void MainWindow::zoomInMode()
{
  mpMapCanvas->setMapTool(mpZoomInTool);
}
void MainWindow::zoomOutMode()
{
  mpMapCanvas->setMapTool(mpZoomOutTool);
}
void MainWindow::addLayer()
{
  QString myLayerPath         = "/home/data/landVN.shp";
  QString myLayerBaseName     = "landVN";
  QString myProviderName      = "ogr";

  QgsVectorLayer * mypLayer = new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);
  QgsSingleSymbolRendererV2 *mypRenderer = new QgsSingleSymbolRendererV2(QgsSymbolV2::defaultSymbol(mypLayer->geometryType()));
  QList<QgsMapCanvasLayer> myLayerSet;
  mypLayer->setRendererV2(mypRenderer);

  if (mypLayer->isValid())
  {
    qDebug("Layer is valid");
  }
  else
  {
    qDebug("Layer is NOT valid");
    return;
  }
  // Add the Vector Layer to the Layer Registry
  QgsMapLayerRegistry::instance()->addMapLayer(mypLayer, true);

  // Add the Layer to the Layer Set
  myLayerSet.append(QgsMapCanvasLayer(mypLayer));
  // set the canvas to the extent of our layer
  mpMapCanvas->setExtent(mypLayer->extent());
  // Set the Map Canvas Layer Set
  mpMapCanvas->setLayerSet(myLayerSet);
}

