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

  int count();
public slots:
  void update();

};



#endif // IMAGECONTROLLER_H
