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
  Bial::Vector<size_t> res;
  for(size_t pxl = 0; pxl <labelImg.ChannelSize(); ++pxl) {
    if( (labelImg[pxl] == color[0]) && (labelImg[(pxl +labelImg.ChannelSize())] == color[1] ) && ( labelImg[(pxl +labelImg.ChannelSize() * 2)]== color[1]) ) {
      res.push_back(pxl);
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
  value.PrintDimensions(std::cout << "Input: ");
//  for( size_t pxl = 0; pxl < 10; ++pxl )
//    value[ pxl ] = 255;
  Bial::Image<int> aux( value );
  aux.PrintDimensions(std::cout << "Aux: ");
 labelImg.PrintDimensions(std::cout << "After: ");
  labelImg = aux;
 labelImg.PrintDimensions(std::cout << "Before: ");
  guiImage.setImageBial(labelImg);
  setPixmap(guiImage.getLabel(0,0));
}


