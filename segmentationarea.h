#ifndef SEGMENTATIONAREA_H
#define SEGMENTATIONAREA_H

#include <Image.hpp>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "Vector.hpp"
#include "Color.hpp"
#include "../bial/gui/inc/guiimage.hpp"
class SegmentationArea : public QGraphicsPixmapItem {
public:
  explicit SegmentationArea(const Bial::Image<int> & img, QGraphicsItem * parent = 0);
  ~SegmentationArea();

  void addPoint(QPointF point, Bial::Vector<float> color);
  void moveTo(QPointF point);
  void clear();
  void updatePath();
  Bial::Vector<size_t> getPoints(Bial::Vector<float> color);

  Bial::Image<int> getLabelImg() const;
  void setLabelImg(const Bial::Image<int> & value);

private:
  //  QPainterPath m_path;
  //  QVector< QVector< QPointF > > lines;
  Bial::Vector<float> lastCoord;
  Bial::Image<int> labelImg;
  Bial::GuiImage guiImage;
};

#endif // SEGMENTATIONAREA_H
