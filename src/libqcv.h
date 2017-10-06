#ifndef LIBQCV_H
#define LIBQCV_H

#include <QImage>
#include <opencv2/core/core.hpp>

namespace QCV {

  static cv::Mat qImageToCV(const QImage &image, bool sharedBuffer);
  static QImage cvToQImage(const cv::Mat &image, bool sharedBuffer);

  static cv::Mat QPixmapToCV(const QPixmap &image, bool sharedBuffer);
  static QPixmap cvToQPixMap(const cv::Mat &image, bool sharedBuffer);

}
#endif // LIBQCV_H
