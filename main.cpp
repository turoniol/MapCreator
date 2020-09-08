#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setOrganizationName("MapCreatorInc");
  QApplication::setApplicationName("MapCreator");

  MainWindow w;
  w.show();
  return a.exec();
}
