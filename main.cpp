//Barış Başmak, Kayacan Vesek 2016400087, 2016400114

#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
 int currentExitCode = 0;

 do {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  currentExitCode = a.exec();
 } while( currentExitCode == MainWindow::EXIT_CODE_REBOOT );

 return currentExitCode;
}
