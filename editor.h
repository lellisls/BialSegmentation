#ifndef EDITOR_H
#define EDITOR_H

#include "segmentationarea.h"

#include <QGraphicsScene>
#include <QObject>

class Editor : public QObject {
  Q_OBJECT
public:
  explicit Editor(QObject *parent = 0);
  ~Editor();
  void install(QGraphicsScene * s);
  void clear();

signals:

public slots:

private:
  SegmentationArea * m_segmentationArea;
  QGraphicsScene * m_scene;
  bool m_scribbling;

  // QObject interface
public:
  bool eventFilter(QObject *, QEvent *evt);
  SegmentationArea * segmentationArea() const;
  void setCurrentImage(const Bial::Image<int> & img);
};

#endif // EDITOR_H
