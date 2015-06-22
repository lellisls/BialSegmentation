#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFileInfoList>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setOrganizationName("GIBIS-UNIFESP");
  app.setApplicationName("BIAL-Segmentation");
  MainWindow w;
  w.showMaximized();
  if( argc == 2 ) {
    QFileInfo info(argv[1]);
    if(info.isFile()) {
      COMMENT("Loading file: " << info.absoluteFilePath().toStdString(), 0);
      w.openFile(info.fileName());
    }else{
      COMMENT("Loading folder: " << info.absoluteFilePath().toStdString(), 0);
      w.loadFolder(QDir(argv[1]));
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
