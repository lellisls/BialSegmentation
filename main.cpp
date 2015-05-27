#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFileInfoList>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setOrganizationName("UNIFESP");
  app.setApplicationName("BIAL");
  MainWindow w;
  w.showMaximized();
  if( argc == 2 ) {
    QFileInfo info(argv[1]);
    if(info.isFile()) {
      w.openFile(info.fileName());
    }else{
      w.loadFolder(info.dir());
    }
  } else {
    QFileInfoList list;
    for( int arg = 1; arg < argc; arg ++ ) {
      list << QFileInfo(argv[arg]);
    }
    w.openList(list);
  }
  return app.exec();
}
