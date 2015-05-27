#include "cursorchanger.h"
#include "graphicsview.h"
#include "../bial/gui/inc/guiimage.hpp"

GraphicsView::GraphicsView(QWidget *parent) :
  QGraphicsView(parent), guiImage(NULL) {
  setScene( new QGraphicsScene(parent) );
  scene()->setBackgroundBrush(QBrush(Qt::black));
  pixmapItem = new QGraphicsPixmapItem();
  maskPixmapItem = new QGraphicsPixmapItem();
  scene()->addItem(pixmapItem);
  scene()->addItem(maskPixmapItem);
  editor.install(scene());
}

void GraphicsView::resizeEvent(QResizeEvent *) {
  fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void GraphicsView::addImage(const QString & filename) {
  files << filename;
  emit setRange(files.size());
}

void GraphicsView::clear() {
  if(guiImage) {
    delete guiImage;
    guiImage = NULL;
  }
  files.clear();
  emit setRange(0);
}

void GraphicsView::clearSegmentationArea() {
  editor.clearSegmentationArea();
  maskPixmapItem->setPixmap(QPixmap());
  mask = Bial::Image<int>(guiImage->getImageBial().Dim());
}

void GraphicsView::loadImage( int pos ) {
  QString filename = files.at(pos);
  if(filename.isEmpty()) {
    return;
  }
  if(guiImage) {
    delete guiImage;
  }
  guiImage = new Bial::GuiImage(filename,(QObject * )parent(),false);
  pixmapItem->setPixmap(guiImage->getPixmap(0,1));
  maskPixmapItem->setPixmap(guiImage->getPixmap(0,1));
  scene()->setSceneRect(pixmapItem->pixmap().rect());
  fitInView(pixmapItem, Qt::KeepAspectRatio);
  editor.setCurrentImage(guiImage->getImageBial());
  mask = Bial::Image<int>(guiImage->getImageBial().Dim());
  currentImg = pos;
  return;
}

void GraphicsView::loadMaskImage( Bial::GuiImage &label ) {
  COMMENT("Loading image label.",0);
  maskPixmapItem->setPixmap(label.getLabel());
}

void GraphicsView::saveMask(const QString & resultsFolder) {
  COMMENT("Writing image label.",0);
  Bial::GuiImage * img = guiImage;
  QDir dir(resultsFolder);
  QFileInfo fileInfo( img->fileName() );
  std::string fname = dir.absoluteFilePath(fileInfo.baseName() + ".pgm").toStdString();
  mask.Write(fname);
}

void GraphicsView::startSegmentation() {
  COMMENT("Start segmentation function.",0);
  CursorChanger cursor(Qt::WaitCursor);
  Bial::GuiImage * img = guiImage;
  COMMENT("Getting object seeds.",0);
  Bial::Vector< size_t > obj ( editor.segmentationArea()->getPoints(2) );
  COMMENT("Getting background seeds.",0);
  Bial::Vector< size_t > bkg ( editor.segmentationArea()->getPoints(3) );
  if(obj.empty() || bkg.empty()) {
    mask = Bial::Image<int>(guiImage->getImageBial().Dim());
    return;
  }
  COMMENT("Calling segmentation and Writing file.",0);
  mask = img->segmentation(obj,bkg);
  Bial::Adjacency adj ( Bial::Adjacency::Circular(1.45) );
  COMMENT("Calculating mask gradient.",0);
  Bial::Image<int> gradient = Bial::Gradient::Morphological(mask, adj);
//  gradient *= 255;
  COMMENT("Generating gradient GuiImage.",0);
  Bial::GuiImage gradient_img( gradient, img->fileName(), parent(), true );
  COMMENT("Loading gradient GuiImage.",0);
  loadMaskImage( gradient_img );
  COMMENT("Reloading image pixmap.",0);
  pixmapItem->setPixmap( img->getPixmap(0,1) );
}
