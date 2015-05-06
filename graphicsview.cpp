#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
  QGraphicsView(parent) {
}

void GraphicsView::resizeEvent(QResizeEvent *) {
  fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
