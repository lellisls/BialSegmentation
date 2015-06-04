#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <guiimage.hpp>

class ImageController : public QObject {
   Q_OBJECT
private:
  QVector<Bial::GuiImage *> m_images;
  QGraphicsPixmapItem * m_pixmapItem;
  int m_currentImagePos;

public:
  ImageController(QObject * parent);

  Bial::GuiImage * currentImage();

  int currentImagePos() const;
  void setCurrentImagePos(int position);

  void addFile(QString fname);
  void openFile(QString fname);

  void clear();
  QGraphicsPixmapItem * pixmapItem() const;
  void setPixmapItem(QGraphicsPixmapItem * value);

public slots:
  void update();

signals:
  void setRange( int value );
};



#endif // IMAGECONTROLLER_H
