#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setOrganizationName("UNIFESP");
  app.setApplicationName("BIAL");
  MainWindow w;
  w.showMaximized();
  return app.exec();
}
