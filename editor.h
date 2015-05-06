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
  SegmentationArea * m_objArea;
  SegmentationArea * m_bkgArea;
  QGraphicsScene * m_scene;
  bool m_scribbling;

  // QObject interface
public:
  bool eventFilter(QObject *, QEvent *evt);
  SegmentationArea * objArea() const;
  SegmentationArea * bkgArea() const;
};

#endif // EDITOR_H
