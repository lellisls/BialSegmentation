#include "segmentationarea.h"
#include "Draw.hpp"
#include <QDebug>
#include <QPen>

SegmentationArea::SegmentationArea(const Bial::Image<int> & img, QGraphicsItem * parent) : QGraphicsPixmapItem(parent), seedsImg( img.Dim(), 3 ), guiImage(img,QString(),NULL,true) {
  guiImage.setLabelType(Bial::GuiImage::enumLabelType::MULTILABEL);
}

SegmentationArea::~SegmentationArea() {

}

void SegmentationArea::addPoint(QPointF point,int color) {
  Bial::Vector < float > currentCoord( { (float)point.rx(), (float)point.ry()} );
  if(!lastCoord.empty()) {
    Bial::Line line (lastCoord,currentCoord);
    line.Draw(seedsImg,color);
  }
  lastCoord = currentCoord;
  guiImage.setImageBial(seedsImg);
  setPixmap(guiImage.getLabel(0,0));
}

void SegmentationArea::moveTo(QPointF point) {
  lastCoord = Bial::Vector < float > ( { (float) point.rx(), (float)point.ry() } );
}

void SegmentationArea::clear() {
  lastCoord.clear();
  setPixmap(QPixmap());
}

Bial::Vector<size_t> SegmentationArea::getPoints(int color) {
  COMMENT( "Converting seeds.", 0 );
  Bial::Vector<size_t> res;
  for(size_t pxl = 0; pxl <seedsImg.size(); ++pxl) {
    if( seedsImg[pxl] == color ) {
      res.push_back( pxl );
    }
  }
  COMMENT( "Returning seeds.", 0 );
  return res;
}

Bial::Image<int> SegmentationArea::getSeedsImg() const {
  return seedsImg;
}

void SegmentationArea::setLabelImg(const Bial::Image<int> & value) {
  COMMENT("Set label image.", 0);
  clear();
  seedsImg = value;
  guiImage.setImageBial(seedsImg);
  setPixmap(guiImage.getLabel(0,0));
}


