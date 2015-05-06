#ifndef SEGMENTATIONAREA_H
#define SEGMENTATIONAREA_H

#include <QGraphicsPathItem>
#include <QObject>

class SegmentationArea : public QGraphicsPathItem {
public:
  explicit SegmentationArea( QGraphicsItem * parent = 0);
  ~SegmentationArea();

  void addPoint(QPointF point);
  void clear();
private:
  QVector< QPointF > points;
};

#endif // SEGMENTATIONAREA_H
