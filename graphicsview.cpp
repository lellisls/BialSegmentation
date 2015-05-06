#include "cursorchanger.h"
#include "graphicsview.h"
#include "../bial/gui/inc/guiimage.hpp"

GraphicsView::GraphicsView(QWidget *parent) :
  QGraphicsView(parent) {
  setScene( new QGraphicsScene(parent) );
  scene()->setBackgroundBrush(QBrush(Qt::black));
  pixmapItem = new QGraphicsPixmapItem();
  scene()->addItem(pixmapItem);
  editor.install(scene());
}

void GraphicsView::resizeEvent(QResizeEvent *) {
  fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

bool GraphicsView::open(const QString & filename) {
  if(filename.isEmpty()) {
    return false;
  }
  images.push_back(new Bial::GuiImage(filename.toStdString(),(QObject * )parent(),false));
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
  pixmapItem->setPixmap(img->getPixmap(0));
  scene()->setSceneRect(pixmapItem->pixmap().rect());
  fitInView(pixmapItem, Qt::KeepAspectRatio);
  editor.clear();
  currentImg = pos;
}

void GraphicsView::startSegmentation() {
  CursorChanger cursor(Qt::WaitCursor);
  Bial::GuiImage * img = images.at(currentImg);
  Bial::Vector< size_t > obj ( editor.objArea()->getPoints(img->width(),img->heigth()) );
  Bial::Vector< size_t > bkg ( editor.bkgArea()->getPoints(img->width(),img->heigth()) );
  img->segmentation(obj,bkg);
}
