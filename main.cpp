#include "mainwindow.h"
#include <QApplication>
#include <qgsapplication.h>


int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();


    // Start the Application
      QgsApplication app(argc, argv, true);
      MainWindow * mypMainWindow = new MainWindow();
      mypMainWindow->show();
      // Start the Application Event Loop
      return app.exec();
}
