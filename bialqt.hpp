#ifndef BIALQT_HPP
#define BIALQT_HPP
#include <QtWidgets>

namespace Bial {
  template< class D, class A > class Image;

  class BialQT {
  public:
    template< class D, class A >
    inline static QImage OpenPNM(Image <D, A> img);

    template< class D, class A >
    inline static QImage OpenPBM(Image <D, A> img);

    template< class D, class A >
    inline static QImage OpenPGM(Image <D, A> img);

    template< class D, class A >
    inline static QImage OpenPPM(Image <D, A> img);

  };

}

#include "Image.hpp"

namespace Bial {

  template< class D, class A >
  QImage BialQT::OpenPNM(Image <D, A> img) {
    if (img.Dims() == 2 && img.Channels() == 3 )
      return (OpenPPM(img));
    if (img.Dims() == 2 && img.Maximum() == 1)
      return (OpenPBM(img));
    if (img.Dims() == 2 && img.Maximum() != 1)
      return (OpenPGM(img));
    return (QImage());
  }

  template< class D, class A >
  QImage BialQT::OpenPBM(Image <D, A> img) {
    QImage image(img.size(0), img.size(1), QImage::Format_RGB32);
    double convert = img.Maximum() / 255.0;
    for (size_t y = 0; y < img.size(1); y++) {
      QRgb *scanLine = (QRgb *) image.scanLine(y);
      for (size_t x = 0; x < img.size(0); x = x + 1) {
        scanLine[x] = qRgb(img(x, y) / convert, img(x, y) / convert, img(x, y) / convert);
      }
    }
    return (image);
  }

  template< class D, class A >
  QImage BialQT::OpenPGM(Image <D, A> img) {
    QImage  image(img.size(0), img.size(1), QImage::Format_RGB32);
    if (img.Maximum() > 4096) {
      for (size_t y = 0; y < img.size(1); y++) {
        QRgb *scanLine = (QRgb *) image.scanLine(y);
        for (size_t x = 0; x < img.size(0); x = x + 1) {
          scanLine[x] = qRgb(img(x, y), img(x, y), img(x, y));
        }
      }
    } else {
      img.SetRange(0, 255);
      for (size_t y = 0; y < img.size(1); y++) {
        QRgb *scanLine = (QRgb *) image.scanLine(y);
        for (size_t x = 0; x < img.size(0); x = x + 1) {
          scanLine[x] = qRgb(img(x, y), img(x, y), img(x, y));
        }
      }
    }
    return (image);
  }

  template< class D, class A >
  QImage BialQT::OpenPPM(Image <D, A> img) {
    QImage image(img.size(0), img.size(1), QImage::Format_RGB32);
    for (size_t y = 0; y < img.size(1); ++y) {
      QRgb *scanLine = (QRgb *) image.scanLine(y);
      for (size_t x = 0; x < img.size(0); ++x) {
        scanLine[x] = qRgb(img(x, y, 0), img(x, y, 1), img(x, y, 2));
      }
    }
    return (image);
  }

}

#endif // BIALQT_HPP
