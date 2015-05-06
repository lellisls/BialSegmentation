#include "segmentationarea.h"
#include "Draw.hpp"
#include <QDebug>
#include <QPen>

SegmentationArea::SegmentationArea( QGraphicsItem * parent, const QColor &color ) : QGraphicsPathItem(parent) {
  setPen(QPen(color,10.0));

}

SegmentationArea::~SegmentationArea() {

}

void SegmentationArea::addPoint(QPointF point) {
  m_path.lineTo(point);
  setPath(m_path);
  if(!lines.isEmpty()){
    lines.back().push_back(point);
  }
}

void SegmentationArea::moveTo(QPointF point) {
  m_path.moveTo(point);
  lines.push_back(QVector<QPointF>(1,point));
}

void SegmentationArea::clear() {
  setPath(QPainterPath());
  m_path = QPainterPath();
  lines.clear();
  update();
}


Bial::Vector<size_t> SegmentationArea::getPoints(size_t width, size_t heigth) {
  Bial::Image< int > img (width,heigth);
  foreach (QVector<QPointF> points, lines) {
    for( int pos = 0; pos < ( points.size() -1 ); ++pos ) {
      QPointF c1 = points.at(pos), c2 = points.at(pos+1);
      Bial::Vector < float > st =  {(float)c1.rx(),(float)c1.ry()};
      Bial::Vector < float > end = {(float)c2.rx(),(float)c2.ry()};
      Bial::Line line (st,end);
      line.Draw(img);
    }
  }

  Bial::Vector<size_t> res;
  for(size_t pxl = 0; pxl < img.size(); ++pxl) {
    if( img[pxl] != 0 ) {
      res.push_back(pxl);
    }
  }
  return res;
}

