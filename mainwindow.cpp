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
  ui(new Ui::MainWindow),
  controller( new ImageController( this )),
  scene( new QGraphicsScene(this)),
  defaultFolder(QDir::homePath()),
  resultsFolder(QDir::temp()) {

  ui->setupUi(this);
  readSettings();
  resultsFolder = QDir::tempPath();

  scene->addItem(controller->pixmapItem());
  ui->graphicsView->setViewNumber(0);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setSegmentationEditor(this);
  loadImage(-1);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::openFile(QString fname) {
  try {
    controller->openFile(fname);
    loadImage(0);
  } catch ( std::logic_error & e ) {
    std::cerr << "Error opening file " << fname.toStdString() << ". " << e.what() << std::endl;
    QMessageBox::warning(this,"Error","Could not open file.",QMessageBox::Ok,QMessageBox::NoButton);
  }
}

void MainWindow::on_actionOpen_triggered() {
  QString fname = QFileDialog::getOpenFileName(this,"Open image",defaultFolder.path(),tr("PGM Images( *pgm *pgm.gz) "));
  if(!fname.isEmpty()) {
    CursorChanger cursor(Qt::WaitCursor);
//    ui->graphicsView->clear();
    openFile(fname);
  }
}

void MainWindow::loadFolder(QDir dir) {
  if(dir.exists()) {
//    ui->graphicsView->clear();
    QStringList filters;
    filters << "*.pgm" << "*.pgm.gz";
    QFileInfoList list = dir.entryInfoList(filters);
    openList(list);
  } else {
    qDebug() << "Directory don't exists.";
  }
}

void MainWindow::on_actionOpen_folder_triggered() {
  QString folder = QFileDialog::getExistingDirectory(this,"Image directory",defaultFolder.path());
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
    settings.setValue("defaultFolder", defaultFolder.path());
    settings.endGroup();
  }
}

void MainWindow::readSettings() {
  COMMENT("Reading QSettings", 1)
  QSettings settings;

  settings.beginGroup("MainWindow");
  QString folder = settings.value("defaultFolder").toString();

  if (folder.isEmpty() ) {
    COMMENT("Didn't have configuration file", 1);
    defaultFolder = QDir::home();

  } else {
    COMMENT("Read settings successfully! Default folder : \"" << defaultFolder.path().toStdString() << "\"", 1);
    defaultFolder.setPath(folder);
  }
}

void MainWindow::loadImage(int position) {
  if(position > 0 && controller->count() > 1 && controller->count() >= position) {
    ui->pushButtonPrevious->setEnabled(true);
  } else {
    ui->pushButtonPrevious->setEnabled(false);
  }
  ui->pushButtonNext->setEnabled( (position + 1) < controller->count() );
  controller->setCurrentImagePos(position);
  if(controller->currentImage()) {
    ui->graphicsView->fitInView(controller->pixmapItem()->boundingRect());
    setWindowTitle("Bial Segmentation ( " + QFileInfo(controller->currentImage()->fileName()).fileName() + " )");
    ui->pushButton->setEnabled(true);
    ui->pushButtonReset->setEnabled(true);
  } else {
    ui->pushButton->setEnabled(false);
    ui->pushButtonNext->setEnabled(false);
    ui->pushButtonPrevious->setEnabled(false);
    ui->pushButtonReset->setEnabled(false);
  }
}

void MainWindow::openList(QFileInfoList list) {
  CursorChanger cursor(Qt::WaitCursor);
  controller->clear();
  foreach( QFileInfo fileInfo, list) {
    if(fileInfo.exists()) {
      try {
        controller->addFile(fileInfo.absoluteFilePath());
      } catch ( std::logic_error & e ) {
        BIAL_WARNING( "Error opening file " << fileInfo.absoluteFilePath().toStdString() << ". " << e.what() );
      } catch ( std::runtime_error & e ) {
        BIAL_WARNING( "Error opening file " << fileInfo.absoluteFilePath().toStdString() << ". " << e.what() );
      }
    }
  }
  if(controller->count() > 0 ) {
    loadImage(0);
  }
}

void MainWindow::start() {
  if(controller->currentImage()) {
    CursorChanger changer(Qt::WaitCursor);
    controller->currentImage()->startSegmentation();
  }
}

void MainWindow::on_pushButton_clicked() {
  start();
}

void MainWindow::on_actionSet_result_folder_triggered() {
  QString temp = QFileDialog::getExistingDirectory(this, tr("Select default folder"), defaultFolder.path());
  COMMENT("Setting default folder: \"" << temp.toStdString() << "\"", 1)
  if (!temp.isEmpty()) {
    resultsFolder = temp;
  } else {
    resultsFolder = QDir::tempPath();
  }
}

void MainWindow::clear() {
  if(controller->currentImage()) {
    controller->currentImage()->segmentationArea()->clear();
    controller->update();
  }
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
  if(controller->currentImagePos() > 0) {
    loadImage(controller->currentImagePos() - 1);
  }
}

void MainWindow::next() {
  if((controller->currentImagePos() + 1) < controller->count() ) {
    loadImage(controller->currentImagePos() + 1);
  }
}

void MainWindow::on_pushButtonNext_clicked() {
  next();
}

void MainWindow::on_actionNext_triggered() {
  next();
}

void MainWindow::on_pushButtonPrevious_clicked() {
  previous();
}

void MainWindow::on_actionPrevious_triggered() {
  previous();
}

void MainWindow::on_actionSave_triggered() {
  if(controller->currentImage()) {
    CursorChanger changer(Qt::WaitCursor);
    QFileInfo fileInfo(controller->currentImage()->fileName());
    QString resultFile = resultsFolder.absoluteFilePath(fileInfo.fileName());
    ui->statusBar->showMessage("Saving file to : " + resultFile);
    controller->currentImage()->startSegmentation().Write(resultFile.toStdString());
  }
}

void MainWindow::paintLabel(QPointF pos, int color, int viewNumber) {
  if(controller->currentImage()) {
    Bial::Vector<float> coord = controller->currentImage()->getBialPosition(pos.toPoint(), viewNumber, 0);
    controller->currentImage()->segmentationArea()->addPoint(coord,color);
    controller->update();
  }
}

void MainWindow::startLine(QPointF pos, int viewNumber) {
  if(controller->currentImage()) {
    Bial::Vector<float> coord = controller->currentImage()->getBialPosition(pos.toPoint(), viewNumber, 0);
    controller->currentImage()->segmentationArea()->moveTo(coord);
    controller->update();
  }
}

void MainWindow::eraseLabel(QPointF pos, int viewNumber) {
  if(controller->currentImage()) {
    Bial::Vector<float> coord = controller->currentImage()->getBialPosition(pos.toPoint(), viewNumber, 0);
    controller->currentImage()->segmentationArea()->addPoint(coord,0,7.0);
    controller->update();
  }
}
