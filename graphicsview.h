#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "editor.h"
#include "Image.hpp"
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

  void clearSegmentationArea();
signals:
  void setRange( int value );

public slots:
  void loadImage(int pos);
  void startSegmentation();

private:
  QVector< Bial::GuiImage * > images;
  QGraphicsPixmapItem * pixmapItem;
  QGraphicsPixmapItem * maskPixmapItem;
  Bial::Image< int > labels;
  Bial::Image< int > mask;
  Editor editor;
  int currentImg;
  void loadLabelsImage( Bial::GuiImage & bialImg );
  void loadMaskImage( Bial::GuiImage & bialImg );
  void saveMask( const QString & resultsFolder );
};

#endif // GRAPHICSVIEW_H
