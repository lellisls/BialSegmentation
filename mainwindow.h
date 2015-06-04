#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagecontroller.h"

#include <QMainWindow>
#include <QCursor>
#include <QApplication>
#include <QFileInfoList>
#include <QDir>
#include <segmentationeditor.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow, public SegmentationEditor {
  Q_OBJECT


public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void openFile(QString fname);
  void openList(QFileInfoList list);
  void loadFolder(QDir dir);
  void loadImage(int position);
private slots:
  void on_actionOpen_triggered();

  void on_actionOpen_folder_triggered();

  void on_actionExit_triggered();

  void on_actionSet_default_folder_triggered();

  void setRange( int value );

  void on_horizontalSlider_sliderMoved(int position);

  void on_pushButton_clicked();

  void on_actionSet_result_folder_triggered();

  void on_pushButtonReset_clicked();

  void on_actionStart_Segmentation_triggered();

  void on_actionReset_seeds_triggered();

  void on_pushButtonPrevious_clicked();

  void on_pushButtonNext_clicked();

  void on_actionNext_triggered();

  void on_actionPrevious_triggered();

  void on_actionSave_triggered();

private:
  void next();
  void previous();
  void readSettings();
  void clear();
  void start();

  Ui::MainWindow *ui;
  ImageController * controller;
  QDir defaultFolder;
  QDir resultsFolder;
  QGraphicsScene * scene;

  // SegmentationEditor interface
public:
  void paintLabel(QPointF pos, int color, int viewNumber);
  void startLine(QPointF pos, int viewNumber);
  void eraseLabel(QPointF pos, int viewNumber);
};

#endif // MAINWINDOW_H
