/*!
  \file libqcv.cpp
  \brief file to define the libqcv functions
*/
#include "libqcv.h"

#include "opencv2/imgproc/imgproc.hpp"


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
    BGRA,
    RGBA,
    ARGB,
  };

  /*!
    \brief Creates a copy of matrix and reverses the color order
    \param matrix the matrix to copy and reverse the color order
    \return a matrix with a BGRA color order
  */
  cv::Mat argbToBGRA(const cv::Mat &matrix) {
    Q_ASSERT_X(matrix.channels() == 4, "argbToBGRA", "Input matrix does not have 4 color channels!");

    // Construct new matrix from old matrix
    cv::Mat newMatrix(matrix.rows, matrix.cols, matrix.type());

    // Create conversion array
    int convertFromTo[] = {0, 3, 1, 2, 2, 1, 3, 0}; // essentially reverses the color order

    const int numOfChannelChanges = 4;
    const int numOfMatrices = 1;

    cv::mixChannels(&matrix, numOfMatrices, &newMatrix, numOfMatrices, convertFromTo, numOfChannelChanges);

    return newMatrix;
  }

  /*!
    \brief Converts argb color order to rgba color order
    \param matrix to convert to the specific color order
    \return a matrix with a RGBA color order
  */
  cv::Mat argbToRGBA(const cv::Mat &matrix) {
    Q_ASSERT_X(matrix.channels() == 4, "argbToRGBA", "Input matrix does not have 4 color channels!");

    // Construct new matrix from old matrix
    cv::Mat newMatrix(matrix.rows, matrix.cols, matrix.type());

    // Create conversion array
    int convertFromTo[] = {0, 3, 1, 0, 2, 1, 3, 2};

    const int numOfChannelChanges = 4;
    const int numOfMatrices = 1;

    cv::mixChannels(&matrix, numOfMatrices, &newMatrix, numOfMatrices, convertFromTo, numOfChannelChanges);

    return newMatrix;
  }

  /*!
    \brief Converts rgba color order to argb color order
    \param matrix to convert to the specific color order
    \return a matrix with a ARGB color order
  */
  cv::Mat rgbaToARGB(const cv::Mat &matrix) {
    Q_ASSERT_X(matrix.channels() == 4, "argbToRGBA", "Input matrix does not have 4 color channels!");

    // Construct new matrix from old matrix
    cv::Mat newMatrix(matrix.rows, matrix.cols, matrix.type());

    // Create conversion array
    int convertFromTo[] = {0, 1, 1, 2, 2, 3, 3, 0};

    const int numOfChannelChanges = 4;
    const int numOfMatrices = 1;

    cv::mixChannels(&matrix, numOfMatrices, &newMatrix, numOfMatrices, convertFromTo, numOfChannelChanges);

    return newMatrix;
  }

  /*!
    \brief Converts bgra color order to rgba color order
    \param matrix to convert to the specific color order
    \return a matrix with a rgba color order
  */
  cv::Mat bgraToRGBA(const cv::Mat &matrix) {
    Q_ASSERT_X(matrix.channels() == 4, "argbToRGBA", "Input matrix does not have 4 color channels!");

    // Construct new matrix from old matrix
    cv::Mat newMatrix(matrix.rows, matrix.cols, matrix.type());

    cv::cvtColor(matrix, newMatrix, CV_BGRA2RGBA);

    return newMatrix;
  }

  cv::Mat adjustColorChannels(const cv::Mat &matrix, ColorOrder srcOrder, ColorOrder destOrder) {
    Q_ASSERT_X(matrix.channels() == 4, "adjustColorChannels", "Input matrix does not have 4 color channels!");

    if(srcOrder == destOrder) {
      return matrix.clone();
    }

    cv::Mat newMatrix;

    if((srcOrder == ColorOrder::ARGB && destOrder == ColorOrder::BGRA) ||
        (srcOrder == ColorOrder::BGRA && destOrder == ColorOrder::ARGB)) {
      newMatrix = argbToBGRA(matrix);
    } else if(srcOrder == ColorOrder::ARGB && destOrder == ColorOrder::RGBA) {
      newMatrix = argbToRGBA(matrix);
    } else if(srcOrder == ColorOrder::RGBA && destOrder == ColorOrder::ARGB) {
      newMatrix = rgbaToARGB(matrix);
    } else {
      newMatrix = bgraToRGBA(matrix);
    }

    return newMatrix;
  }

  /*!
    \brief Finds the closest QImage format that is compatible with OpenCV
    \param current the current QImage format
    \return the closest compatible QImage format
  */
  QImage::Format getClosestFormat(const QImage::Format current) {
    switch(current) {
      case QImage::Format_Invalid:
        return QImage::Format_ARGB32;

      case QImage::Format_Mono:
      case QImage::Format_MonoLSB:
        return QImage::Format_Indexed8;

      case QImage::Format_Indexed8:
      case QImage::Format_RGB32:
      case QImage::Format_ARGB32:
      case QImage::Format_ARGB32_Premultiplied:
        return current;

#if QT_VERSION > 0x040400

      case QImage::Format_RGB16:
        return QImage::Format_RGB32;

      case QImage::Format_ARGB8565_Premultiplied:
      case QImage::Format_ARGB6666_Premultiplied:
      case QImage::Format_ARGB8555_Premultiplied:
      case QImage::Format_ARGB4444_Premultiplied:
        return QImage::Format_ARGB32_Premultiplied;

      case QImage::Format_RGB666:
      case QImage::Format_RGB555:
      case QImage::Format_RGB444:
      case QImage::Format_RGB888:
        return QImage::Format_RGB888;
#endif

#if QT_VERSION > 0x050200

      case QImage::Format_RGBX8888:
      case QImage::Format_RGBA8888:
      case QImage::Format_RGBA8888_Premultiplied:
        return current;
#endif

      case QImage::Format_BGR30:
      case QImage::Format_A2BGR30_Premultiplied:
      case QImage::Format_RGB30:
      case QImage::Format_A2RGB30_Premultiplied:
        return QImage::Format_ARGB32;

      case QImage::Format_Alpha8:
      case QImage::Format_Grayscale8:
        return current;

      case QImage::NImageFormats:
        return QImage::Format_ARGB32;
    }
  }

  /*!
    \brief Function to get endian dependedent color order
    \return returns the color order depending on system byte order
  */
  ColorOrder getEndianDependentColorOrder() {
    if(Q_BYTE_ORDER == Q_BIG_ENDIAN) {
      return ColorOrder::ARGB;
    } else {
      return ColorOrder::BGRA;
    }
  }

  ColorOrder getColorOrderFor(const QImage::Format &format) {
    switch(format) {
      case QImage::Format_Indexed8:
        break;

      case QImage::Format_RGB32:
      case QImage::Format_ARGB32:
      case QImage::Format_ARGB32_Premultiplied:
        return getEndianDependentColorOrder();
#if QT_VERSION > 0x040400

      case QImage::Format_RGB888:
        return ColorOrder::RGBA;
#endif
#if QT_VERSION > 0x050200

      case QImage::Format_RGBX8888:
      case QImage::Format_RGBA8888:
      case QImage::Format_RGBA8888_Premultiplied:
        return ColorOrder::RGBA;
#endif
#if QT_VERSION > 0x050500

      case QImage::Format_Alpha8:
      case QImage::Format_Grayscale8:
#endif

      default:
        return ColorOrder::RGBA;
    }
  }

  /*!
    \brief Function to convert a QImage to a cv::Mat
    \param image reference to the QImage to convert
    \param sharedBuffer boolean to pass if the buffers should be shared
    \return returns an OpenCV Matrix
  */
  cv::Mat QCV::qImageToCV(const QImage &image, bool sharedBuffer) {
    if(image.isNull()) {
      return cv::Mat();
    }

    QImage::Format format = getClosestFormat(image.format());
    QImage localImage = (format == image.format()) ? image : image.convertToFormat(format);

    ColorOrder order;


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

