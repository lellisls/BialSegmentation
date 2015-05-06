#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "segmentationarea.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

namespace Bial {
  class GuiImage;
}

class GraphicsView : public QGraphicsView {
  Q_OBJECT
public:
  explicit GraphicsView(QWidget *parent = 0);
  void resizeEvent( QResizeEvent * );

  void clear();

  bool open( const QString & filename );

signals:
  void setRange( int value );

public slots:
  void loadImage(int pos);

private:
  QVector< Bial::GuiImage * > images;
  QGraphicsPixmapItem * pixmapItem;
  SegmentationArea * objArea;
  SegmentationArea * bkgArea;

  // QWidget interface
protected:
  void mousePressEvent(QMouseEvent *me);
  void mouseReleaseEvent(QMouseEvent *me);
  void mouseMoveEvent(QMouseEvent *me);
};

#endif // GRAPHICSVIEW_H
