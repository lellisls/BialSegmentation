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
  void saveMask( const QString & resultsFolder );
  void addImage( const QString & filename);
  void clearSegmentationArea();
signals:
  void setRange( int value );

public slots:
  void loadImage(int pos);
  void startSegmentation();

private:
//  QVector< Bial::GuiImage * > images;
  Bial::GuiImage * guiImage;
  QStringList files;
  QGraphicsPixmapItem * pixmapItem;
  QGraphicsPixmapItem * maskPixmapItem;
  Bial::Image< int > labels;
  Bial::Image< int > mask;
  Editor editor;
  int currentImg;
  void loadLabelsImage( Bial::GuiImage & bialImg );
  void loadMaskImage( Bial::GuiImage & bialImg );
};

#endif // GRAPHICSVIEW_H
