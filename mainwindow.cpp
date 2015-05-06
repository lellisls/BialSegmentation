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

void MainWindow::on_actionOpen_triggered() {
  QString fname = QFileDialog::getOpenFileName(this,"Open image",defaultFolder,tr("NetPBM Images( *.pbm *pgm *.ppm *.pnm *.pbm.gz *pgm.gz *.ppm.gz *.pnm.gz) "));
  if(!fname.isEmpty()) {
    CursorChanger cursor(Qt::WaitCursor);
    try {
      ui->graphicsView->clear();
      ui->graphicsView->open(fname);
    } catch ( std::logic_error & e ) {
      std::cerr << "Error opening file " << fname.toStdString() << ". " << e.what() << std::endl;
      QMessageBox::warning(this,"Error","Could not open file.",QMessageBox::Ok,QMessageBox::NoButton);
    }
  }
}

void MainWindow::on_actionOpen_folder_triggered() {
  QString folder = QFileDialog::getExistingDirectory(this,"Image directory",defaultFolder);
  QDir dir( folder );
  if(dir.exists()) {
    ui->graphicsView->clear();
    QStringList filters;
    filters << "*.pbm" << "*.pgm" << "*.ppm" << "*.pnm" << "*.pbm.gz" << "*.pgm.gz" << "*.ppm.gz" << "*.pnm.gz";
    QStringList list = dir.entryList(filters);
    CursorChanger cursor(Qt::WaitCursor);
    for( int fl = 0; fl < list.size(); ++fl ) {
      QString fname = list[fl];
      try {
        ui->graphicsView->open(dir.absoluteFilePath(fname));
      } catch ( std::logic_error & e ) {
        std::cerr << "Error opening file " << fname.toStdString() << ". " << e.what() << std::endl;
      } catch ( std::runtime_error & e ) {
        std::cerr << "Error opening file " << fname.toStdString() << ". " << e.what() << std::endl;
      }
    }
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
