#ifndef SEGMENTATIONAREA_H
#define SEGMENTATIONAREA_H

#include <QGraphicsPathItem>
#include <QObject>
#include "Vector.hpp"
class SegmentationArea : public QGraphicsPathItem {
public:
  explicit SegmentationArea(QGraphicsItem * parent = 0, const QColor & color = Qt::red);
  ~SegmentationArea();

  void addPoint(QPointF point);
  void moveTo(QPointF point);
  void clear();
  void updatePath();
  Bial::Vector<size_t> getPoints(size_t width, size_t heigth);
private:
  QPainterPath m_path;
  QVector< QVector< QPointF > > lines;
};

#endif // SEGMENTATIONAREA_H
