/*!
  \file libqcv.h
  \brief file to define the libqcv namespace
*/

#ifndef LIBQCV_H
#define LIBQCV_H

#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>

/*!
  \brief Contains general conversion function between OpenCV and Qt
*/
namespace QCV {

  static cv::Mat qImageToCV(const QImage &image, bool sharedBuffer=false);
  static QImage cvToQImage(const cv::Mat &image, bool sharedBuffer=false);

  static cv::Mat QPixmapToCV(const QPixmap &image, bool sharedBuffer=false);
  static QPixmap cvToQPixmap(const cv::Mat &image, bool sharedBuffer=false);
}
#endif // LIBQCV_H
