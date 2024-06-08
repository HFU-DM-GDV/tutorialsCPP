#include "util.h"

namespace util {
    void copyToImgRegion(cv::Mat& dest, cv::Mat& src, int x, int y, int width, int height) {
        cv::Rect insertRoi{x, y, width, height};

        cv::Mat resizedSrc = src.clone();
        cv::resize(resizedSrc, resizedSrc, cv::Size(width, height));

        cv::Mat destRoi = dest(insertRoi);
        resizedSrc.copyTo(destRoi);
    }

    cv::Mat generateTransformationMatrix(const std::vector<float> &values) {
        assert(values.size() == 6 && "Exactly 6 values have to be provided");

        cv::Mat transformMat = cv::Mat::zeros(2, 3, CV_32F);
        std::memcpy(transformMat.data, values.data(), 6 * sizeof(float));

        return transformMat;
    }

    std::vector<int> randomInRange(int from, int to, int amount) {
        std::random_device rd;
        std::mt19937 gen{rd()};
        std::uniform_int_distribution<> distr(from, to);

        std::vector<int> randNums;

        for (size_t i = 0; i < amount; i++) {
            randNums.push_back(distr(gen));
        }

        return std::move(randNums);
    }
}
