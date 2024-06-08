#ifndef GDV_UTIL_H
#define GDV_UTIL_H

#include <vector>
#include <cassert>
#include <random>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace util {
    void copyToImgRegion(cv::Mat& dest, cv::Mat& src, int x, int y, int width, int height);
    cv::Mat generateTransformationMatrix(const std::vector<float>& values);
    std::vector<int> randomInRange(int from, int to, int amount);
}
#endif //GDV_UTIL_H
