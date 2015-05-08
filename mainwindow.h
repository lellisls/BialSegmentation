#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCursor>
#include <QApplication>
#include <QFileInfoList>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void openFile(QString fname);
  void openList(QFileInfoList list);
private slots:
  void on_actionOpen_triggered();

  void on_actionOpen_folder_triggered();

  void on_actionExit_triggered();

  void on_actionSet_default_folder_triggered();

  void setRange( int value );

  void on_horizontalSlider_sliderMoved(int position);

  void on_pushButton_clicked();

  void on_actionSet_result_folder_triggered();

private:

  void readSettings();

  Ui::MainWindow *ui;
  QString defaultFolder;
  QString resultsFolder;
};

#endif // MAINWINDOW_H
