#include "cursorchanger.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QSettings>
#include "Common.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  readSettings();
  setRange(0);
  connect(ui->graphicsView,&GraphicsView::setRange,this,&MainWindow::setRange);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::openFile(QString fname) {
  try {
    ui->graphicsView->open(fname);
  } catch ( std::logic_error & e ) {
    std::cerr << "Error opening file " << fname.toStdString() << ". " << e.what() << std::endl;
    QMessageBox::warning(this,"Error","Could not open file.",QMessageBox::Ok,QMessageBox::NoButton);
  }
}

void MainWindow::on_actionOpen_triggered() {
  QString fname = QFileDialog::getOpenFileName(this,"Open image",defaultFolder,tr("NetPBM Images( *.pbm *pgm *.ppm *.pnm *.pbm.gz *pgm.gz *.ppm.gz *.pnm.gz) "));
  if(!fname.isEmpty()) {
    CursorChanger cursor(Qt::WaitCursor);
    ui->graphicsView->clear();
    openFile(fname);
  }
}

void MainWindow::on_actionOpen_folder_triggered() {
  QString folder = QFileDialog::getExistingDirectory(this,"Image directory",defaultFolder);
  QDir dir( folder );
  if(dir.exists()) {
    ui->graphicsView->clear();
    QStringList filters;
    filters << "*.pbm" << "*.pgm" << "*.ppm" << "*.pnm" << "*.pbm.gz" << "*.pgm.gz" << "*.ppm.gz" << "*.pnm.gz";
    QFileInfoList list = dir.entryInfoList(filters);
    openList(list);
  }
}

void MainWindow::on_actionExit_triggered() {
  close();
}

void MainWindow::on_actionSet_default_folder_triggered() {
  QDir dir;

  if (!dir.exists(QDir::homePath() + "/.bial/")) { //
    dir.mkdir(QDir::homePath() + "/.bial/");
  }

  QString temp = QFileDialog::getExistingDirectory(this, tr("Select default folder"));
  COMMENT("Setting default folder: \"" << temp.toStdString() << "\"", 1)

  if (!temp.isEmpty()) {

    defaultFolder = temp;

    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("defaultFolder", defaultFolder);
    settings.endGroup();
  }
}

void MainWindow::setRange(int value) {
  ui->horizontalSlider->setEnabled( value > 1 );
  ui->horizontalSlider->setRange(0,value);
}

void MainWindow::readSettings() {
  COMMENT("Reading QSettings", 1)
  QSettings settings;

  settings.beginGroup("MainWindow");
  defaultFolder = settings.value("defaultFolder").toString();

  if (!defaultFolder.isEmpty()) {
    COMMENT("Read settings successfully! Default folder : \"" << defaultFolder.toStdString() << "\"", 1)
  } else {
    COMMENT("Didn't have configuration file", 1)
    defaultFolder = QDir::homePath();
  }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {
  ui->graphicsView->loadImage(position);
}

void MainWindow::openList(QFileInfoList list) {
  CursorChanger cursor(Qt::WaitCursor);
  foreach( QFileInfo fileInfo, list) {
    if(fileInfo.exists()) {
      try {
        ui->graphicsView->open(fileInfo.absoluteFilePath());
      } catch ( std::logic_error & e ) {
        BIAL_WARNING( "Error opening file " << fileInfo.absoluteFilePath().toStdString() << ". " << e.what() );
      } catch ( std::runtime_error & e ) {
        BIAL_WARNING( "Error opening file " << fileInfo.absoluteFilePath().toStdString() << ". " << e.what() );
      }
    }
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->graphicsView->startSegmentation();
}

void MainWindow::on_actionSet_result_folder_triggered() {
  QString temp = QFileDialog::getExistingDirectory(this, tr("Select default folder"), defaultFolder);
  COMMENT("Setting default folder: \"" << temp.toStdString() << "\"", 1)

  if (!temp.isEmpty()) {
    resultsFolder = temp;
  } else {
    resultsFolder = QDir::tempPath();
  }
}
