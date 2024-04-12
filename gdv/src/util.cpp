#include "util.h"

namespace util {
    void copyToImgRegion(cv::Mat& dest, cv::Mat& src, int x, int y, int width, int height) {
        cv::Rect insertRoi{x, y, width, height};

        cv::Mat resizedSrc = src.clone();
        cv::resize(resizedSrc, resizedSrc, cv::Size(width, height));

        cv::Mat destRoi = dest(insertRoi);
        resizedSrc.copyTo(destRoi);
    }
}
