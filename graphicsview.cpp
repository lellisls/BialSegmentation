#include "cursorchanger.h"
#include "graphicsview.h"
#include "../bial/gui/inc/guiimage.hpp"

GraphicsView::GraphicsView(QWidget *parent) :
  QGraphicsView(parent) {
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

bool GraphicsView::open(const QString & filename) {
  if(filename.isEmpty()) {
    return false;
  }
  images.push_back(new Bial::GuiImage(filename,(QObject * )parent(),false));
  emit setRange(images.size());
  loadImage(0);
  return true;
}

void GraphicsView::clear() {
  foreach (Bial::GuiImage * image, images) {
    delete image;
  }
  images.clear();
  emit setRange(0);
}

void GraphicsView::loadImage( int pos ) {
  Bial::GuiImage * img = images.at(pos);
  pixmapItem->setPixmap(img->getPixmap(0,1));
  maskPixmapItem->setPixmap(img->getPixmap(0,1));
  scene()->setSceneRect(pixmapItem->pixmap().rect());
  fitInView(pixmapItem, Qt::KeepAspectRatio);
  editor.setCurrentImage(img->getImageBial());
  currentImg = pos;
  mask = Bial::Image<int>();
}

void GraphicsView::loadMaskImage( Bial::GuiImage &label ) {
  COMMENT("Loading image label.",0);
  maskPixmapItem->setPixmap(label.getLabel());
}

void GraphicsView::saveMask(const QString & resultsFolder) {
  COMMENT("Writing image label.",0);
  Bial::GuiImage * img = images.at(currentImg);
  QDir dir(resultsFolder);
  QFileInfo fileInfo( img->getFileName() );
  std::string fname = dir.absoluteFilePath(fileInfo.baseName()).toStdString();
  mask.Write(fname);
}

void GraphicsView::startSegmentation() {
  COMMENT("Start segmentation function.",0);
  CursorChanger cursor(Qt::WaitCursor);
  Bial::GuiImage * img = images.at(currentImg);
  COMMENT("Getting object seeds.",0);
  Bial::Vector< size_t > obj ( editor.segmentationArea()->getPoints(2) );
  COMMENT("Getting background seeds.",0);
  Bial::Vector< size_t > bkg ( editor.segmentationArea()->getPoints(3) );
  COMMENT("Calling segmentation and Writing file.",0);
  mask = img->segmentation(obj,bkg);
  Bial::Adjacency adj ( Bial::Adjacency::Circular(1.45) );
  COMMENT("Calculating mask gradient.",0);
  Bial::Image<int> gradient = Bial::Gradient::Morphological(mask, adj);
//  gradient *= 255;
  COMMENT("Generating gradient GuiImage.",0);
  Bial::GuiImage gradient_img( gradient, img->getFileName(), parent(), true );
  COMMENT("Loading gradient GuiImage.",0);
  loadMaskImage( gradient_img );
  COMMENT("Reloading image pixmap.",0);
  pixmapItem->setPixmap( img->getPixmap(0,1) );
}
