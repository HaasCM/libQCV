/*!
  \file libqcv.cpp
  \brief file to define the libqcv functions
*/
#include "libqcv.h"

#include "opencv2/imgproc/imgproc.hpp"


//TODO argb to bgra conversion
//TODO handling cv channel order adjustments
//TODO format conversion logic
//TODO 32bit to 64bit sys conversion??
//TODO implement???

/*!
  \brief Contains general conversion function between OpenCV and Qt
*/
namespace QCV {
  /*!
    \enum ColorOrder
    \brief enum to define the color order
  */
  enum class ColorOrder {
    BGR,
    RGB,
    ARGB,
  };

  /*!
    \brief Function to convert a QImage to a cv::Mat
    \param image reference to the QImage to convert
    \param sharedBuffer boolean to pass if the buffers should be shared
    \return returns an OpenCV Matrix
  */
  cv::Mat QCV::qImageToCV(const QImage &image, bool sharedBuffer) {

  }

  /*!
    \brief Function to convert an OpenCV matric to a QImage
    \param image  a const reference to the matrix to convert
    \param sharedBuffer boolean to pass if the buffers should be shared
    \return returns a QImage
  */
  QImage QCV::cvToQImage(const cv::Mat &image, bool sharedBuffer) {

  }

  /*!
    \brief Function to convert a QPixmap to an OpenCV Matrix
    \param image a const reference to the QPixmap to convert
    \param sharedBuffer boolean to pass if the buffers should be shared
    \return returns a converted OpenCV Matrix
  */
  cv::Mat QCV::QPixmapToCV(const QPixmap &image, bool sharedBuffer) {

  }

  /*!
    \brief Function to convert an OpenCV matrix to a QPixmap
    \param image a const reference to the OpenCV matrix to convert
    \param sharedBuffer a boolean to pass if the buffers should be shared
    \return returns a converted QPixmap
  */
  QPixmap QCV::cvToQPixmap(const cv::Mat &image, bool sharedBuffer) {

  }
}

