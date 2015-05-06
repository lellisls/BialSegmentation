#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "editor.h"

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
  void startSegmentation();

private:
  QVector< Bial::GuiImage * > images;
  QGraphicsPixmapItem * pixmapItem;
  Editor editor;
  int currentImg;
};

#endif // GRAPHICSVIEW_H
