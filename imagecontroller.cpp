#include "imagecontroller.h"

ImageController::ImageController(QObject * parent) :
  QObject(parent),
  m_pixmapItem(new QGraphicsPixmapItem()),
  m_currentImagePos(-1) {

}

QGraphicsPixmapItem * ImageController::pixmapItem() const {
  return m_pixmapItem;
}

void ImageController::setPixmapItem(QGraphicsPixmapItem * value) {
  m_pixmapItem = value;
}

void ImageController::update() {
  if(currentImage()) {
    m_pixmapItem->setPixmap( currentImage()->getSlice(0,0) );
  }
}

int ImageController::currentImagePos() const {
  return m_currentImagePos;
}

void ImageController::setCurrentImagePos(int position) {
  if(currentImage()) {
    disconnect(currentImage(),&Bial::GuiImage::imageUpdated,this,&ImageController::update);
  }
  m_currentImagePos = position;
  if(currentImage()) {
    connect(currentImage(),&Bial::GuiImage::imageUpdated,this,&ImageController::update);
  }
  update();
}

void ImageController::addFile(QString fname) {
  m_images.append(new Bial::GuiImage(fname,this));
}

void ImageController::openFile(QString fname) {
  clear();
  addFile(fname);
  setCurrentImagePos(0);
}

void ImageController::clear() {
  m_images.clear();
  setCurrentImagePos(-1);
}

int ImageController::count() {
  return m_images.size();
}

Bial::GuiImage *ImageController::currentImage() {
  if(m_currentImagePos >= 0 && m_currentImagePos < m_images.size()) {
    return (m_images.at(m_currentImagePos));
  }
  return NULL;
}

