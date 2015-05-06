#include "cursorchanger.h"
#include <QApplication>

CursorChanger::CursorChanger(const QCursor & cursor) {
  QApplication::setOverrideCursor(cursor);
}

CursorChanger::~CursorChanger() {
  QApplication::setOverrideCursor(Qt::ArrowCursor);
}
