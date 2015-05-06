#include "editor.h"

#include <QGraphicsSceneMouseEvent>
#include <qdebug.h>

Editor::Editor(QObject *parent) : QObject(parent), m_scribbling(false) {
  m_objArea = new SegmentationArea(0,Qt::red);
  m_bkgArea = new SegmentationArea(0,Qt::blue);
}

Editor::~Editor() {
  delete m_objArea;
  delete m_bkgArea;
}

void Editor::install(QGraphicsScene * scn) {
  m_scene = scn;
  m_scene->installEventFilter(this);
  m_scene->addItem(m_objArea);
  m_scene->addItem(m_bkgArea);
  m_objArea->show();
  m_bkgArea->show();
}

void Editor::clear() {
  m_objArea->clear();
  m_bkgArea->clear();
}

SegmentationArea * Editor::bkgArea() const {
  return m_bkgArea;
}

SegmentationArea * Editor::objArea() const {
  return m_objArea;
}

bool Editor::eventFilter(QObject * obj, QEvent * evt) {
  QGraphicsSceneMouseEvent *me = dynamic_cast<QGraphicsSceneMouseEvent*>(evt);
  if(me != NULL ) {
    switch ((int) evt->type()) {
    case QEvent::GraphicsSceneMousePress : {
        if(me->button() == Qt::LeftButton) {
          m_objArea->moveTo(me->scenePos());
          m_scribbling = true;
        } else if(me->button() == Qt::RightButton) {
          m_bkgArea->moveTo(me->scenePos());
          m_scribbling = true;
        }
        break;
      }
    case QEvent::GraphicsSceneMouseMove : {
        if(m_scribbling) {
          if(me->buttons() & Qt::LeftButton) {
            m_objArea->addPoint(me->scenePos());
          } else if(me->buttons() & Qt::RightButton) {
            m_bkgArea->addPoint(me->scenePos());
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
