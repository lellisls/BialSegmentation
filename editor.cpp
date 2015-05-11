#include "editor.h"

#include <QGraphicsSceneMouseEvent>
#include <qdebug.h>

Editor::Editor(QObject *parent) : QObject(parent), m_scribbling(false) {
  m_segmentationArea = new SegmentationArea(Bial::Image<int>(100,100));
}

Editor::~Editor() {
  delete m_segmentationArea;
}

void Editor::install(QGraphicsScene * scn) {
  m_scene = scn;
  m_scene->installEventFilter(this);
  m_scene->addItem(m_segmentationArea);
  m_segmentationArea->show();
}

void Editor::clear() {
  m_segmentationArea->clear();
}

SegmentationArea * Editor::segmentationArea() const {
  return m_segmentationArea;
}

void Editor::setCurrentImage( const Bial::Image<int> & img ) {
  m_segmentationArea->setLabelImg(Bial::Image<int>(img.Dim()));
}

bool Editor::eventFilter(QObject * obj, QEvent * evt) {
  QGraphicsSceneMouseEvent *me = dynamic_cast<QGraphicsSceneMouseEvent*>(evt);
  if(me != NULL ) {
    switch ((int) evt->type()) {
    case QEvent::GraphicsSceneMousePress : {
        m_segmentationArea->moveTo(me->scenePos());
        m_scribbling = true;
        break;
      }
    case QEvent::GraphicsSceneMouseMove : {
        if(m_scribbling) {
          if(me->buttons() & Qt::LeftButton) {
            m_segmentationArea->addPoint(me->scenePos(),2);
          } else if(me->buttons() & Qt::RightButton) {
            m_segmentationArea->addPoint(me->scenePos(),3);
          }
        }
        break;
      }
    case QEvent::GraphicsSceneMouseRelease : {
        m_scribbling = false;
        break;
      }
    default: {
        break;
      }
    }
  }
  return QObject::eventFilter(obj, evt);
}
