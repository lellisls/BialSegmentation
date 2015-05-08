#include "segmentationarea.h"
#include "Draw.hpp"
#include <QDebug>
#include <QPen>
#include <QTime>

SegmentationArea::SegmentationArea(const Bial::Image<int> & img, QGraphicsItem * parent) : QGraphicsPixmapItem(parent), labelImg( img.Dim(), 3 ), guiImage(img,QString(),NULL,true) {

}

SegmentationArea::~SegmentationArea() {

}

void SegmentationArea::addPoint(QPointF point, Bial::Vector< float> color ) {
  Bial::Vector < float > currentCoord( { (float)point.rx(), (float)point.ry()} );
  if(!lastCoord.empty()) {
    Bial::Line line (lastCoord,currentCoord,color);
    line.Draw(labelImg);
  }
  lastCoord = currentCoord;
  guiImage.setImageBial(labelImg);
  setPixmap(guiImage.getLabel(0,0));
}

void SegmentationArea::moveTo(QPointF point) {
  lastCoord = Bial::Vector < float > ( { (float) point.rx(), (float)point.ry() } );
}

void SegmentationArea::clear() {
  lastCoord.clear();
  setPixmap(QPixmap());
}

Bial::Vector<size_t> SegmentationArea::getPoints(Bial::Vector< float> color) {
  COMMENT( "Converting seeds.", 0 );
  if(labelImg.Channels() != color.size() ) {
    BIAL_WARNING( "Color and image channels do not match." );
  }
  Bial::Vector<size_t> res;
  for(size_t x = 0; x <labelImg.size(0); ++x) {
    for(size_t y = 0; y <labelImg.size(1); ++y) {
      bool isEqual = true;
      for(size_t clr = 0; clr < color.size(); ++clr ){
        if( ! ( (labelImg(x,y,clr) == color[clr]) || (labelImg(x,y,clr) !=0 && color[clr] != 0) ) ) {
          isEqual = false;
        }
      }
      if(isEqual) {
        res.push_back( labelImg.Position(x, y) );
      }
    }
  }
  COMMENT( "Returning seeds.", 0 );
  return res;
}

Bial::Image<int> SegmentationArea::getLabelImg() const {
  return labelImg;
}

void SegmentationArea::setLabelImg(const Bial::Image<int> & value) {
  COMMENT("Set label image.", 0);
  clear();
  labelImg = value;
  guiImage.setImageBial(labelImg);
  setPixmap(guiImage.getLabel(0,0));
}


