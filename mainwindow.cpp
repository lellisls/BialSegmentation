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
  resultsFolder = QDir::tempPath();
//  QShortcut * refreshShortcut = new QShortcut(QKeySequence( Qt::CTRL + Qt::Key_R),this);
//  connect(refreshShortcut,&QShortcut::activated,this,&MainWindow::on_pushButtonReset_clicked);
//  QShortcut * segmentateShortcut = new QShortcut(QKeySequence( Qt::CTRL + Qt::Key_Space),this);
//  connect(segmentateShortcut,&QShortcut::activated,this,&MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::openFile(QString fname) {
  try {
    ui->graphicsView->clear();
    ui->graphicsView->addImage(fname);
    ui->graphicsView->loadImage(0);
  } catch ( std::logic_error & e ) {
    std::cerr << "Error opening file " << fname.toStdString() << ". " << e.what() << std::endl;
    QMessageBox::warning(this,"Error","Could not open file.",QMessageBox::Ok,QMessageBox::NoButton);
  }
}

void MainWindow::on_actionOpen_triggered() {
  QString fname = QFileDialog::getOpenFileName(this,"Open image",defaultFolder,tr("PGM Images( *pgm *pgm.gz) "));
  if(!fname.isEmpty()) {
    CursorChanger cursor(Qt::WaitCursor);
    ui->graphicsView->clear();
    openFile(fname);
  }
}

void MainWindow::loadFolder(QDir dir) {
  if(dir.exists()) {
    ui->graphicsView->clear();
    QStringList filters;
    filters << "*.pgm" << "*.pgm.gz";
    QFileInfoList list = dir.entryInfoList(filters);
    openList(list);
  }else{
    qDebug() << "Directory don't exists.";
  }
}

void MainWindow::on_actionOpen_folder_triggered() {
  QString folder = QFileDialog::getExistingDirectory(this,"Image directory",defaultFolder);
  loadFolder(QDir(folder));
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
  ui->horizontalSlider->setRange(0,value -1);
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

void MainWindow::loadImage(int position) {
  if(position <= 0) {
    ui->pushButtonPrevious->setEnabled(false);
  }
  if(ui->horizontalSlider->maximum() > 0 && ui->horizontalSlider->maximum() > position) {
    ui->pushButtonPrevious->setEnabled(true);
  }
  ui->graphicsView->loadImage(position);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {
  loadImage(position);
}

void MainWindow::openList(QFileInfoList list) {
  CursorChanger cursor(Qt::WaitCursor);
  foreach( QFileInfo fileInfo, list) {
    if(fileInfo.exists()) {
      try {
        ui->graphicsView->addImage(fileInfo.absoluteFilePath());
      } catch ( std::logic_error & e ) {
        BIAL_WARNING( "Error opening file " << fileInfo.absoluteFilePath().toStdString() << ". " << e.what() );
      } catch ( std::runtime_error & e ) {
        BIAL_WARNING( "Error opening file " << fileInfo.absoluteFilePath().toStdString() << ". " << e.what() );
      }
    }
  }
  if(ui->horizontalSlider->maximum() > 0 ) {
    ui->graphicsView->loadImage(0);
  }
}

void MainWindow::start() {
  ui->graphicsView->startSegmentation();
}

void MainWindow::on_pushButton_clicked() {
  start();
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

void MainWindow::clear() {
  ui->graphicsView->clearSegmentationArea();
}

void MainWindow::on_pushButtonReset_clicked() {
  clear();
}

void MainWindow::on_actionStart_Segmentation_triggered() {
  start();
}

void MainWindow::on_actionReset_seeds_triggered() {
  clear();
}

void MainWindow::previous() {
  if(ui->horizontalSlider->value() > 0) {
    ui->horizontalSlider->setValue(ui->horizontalSlider->value() -1);
    ui->graphicsView->loadImage(ui->horizontalSlider->value());
  }
}

void MainWindow::on_pushButtonPrevious_clicked() {
  previous();
}

void MainWindow::next() {
  if(ui->horizontalSlider->value() < ui->horizontalSlider->maximum()) {
    ui->horizontalSlider->setValue(ui->horizontalSlider->value() +1);
    ui->graphicsView->loadImage(ui->horizontalSlider->value());
  }
}

void MainWindow::on_pushButtonNext_clicked() {
  next();
}

void MainWindow::on_actionNext_triggered() {
  next();
}

void MainWindow::on_actionPrevious_triggered() {
  previous();
}

void MainWindow::on_actionSave_triggered() {
  ui->graphicsView->saveMask(resultsFolder);
}
