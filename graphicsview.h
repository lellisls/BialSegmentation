#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

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
};

#endif // GRAPHICSVIEW_H
