#include "segmentationarea.h"

SegmentationArea::SegmentationArea(QGraphicsItem * parent) : QGraphicsPathItem(parent) {

}

SegmentationArea::~SegmentationArea() {

}

void SegmentationArea::addPoint(QPointF point) {
  points.push_back(point);
}

void SegmentationArea::clear() {
  points.clear();
  setPath(QPainterPath());
  update();
}

