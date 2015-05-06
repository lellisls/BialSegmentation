#include "mainwindow.h"
#include <QApplication>
#include <QFileInfoList>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setOrganizationName("UNIFESP");
  app.setApplicationName("BIAL");
  MainWindow w;
  w.showMaximized();
  QFileInfoList list;
  for( int arg = 1; arg < argc; arg ++ ) {
    list << QFileInfo(argv[arg]);
  }
  w.openList(list);
  return app.exec();
}
