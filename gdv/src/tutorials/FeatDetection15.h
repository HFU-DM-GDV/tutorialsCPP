#ifndef GDV_FEATDETECTION15_H
#define GDV_FEATDETECTION15_H

#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../util.h"

using namespace cv;

class FeatDetection15 {
private:
    const char* m_imgPath = "../data/images/window01.JPG";
    const char* m_windowName = "Feature detection";

    // Slider names
    const char* m_sliderMaxFeatures = "Max features";
    const char* m_sliderMinQuality = "Min quality";
    const char* m_sliderMinEuclidDistance = "Min euclid distance";

    // Matrix refs
    Mat m_originalImg;
    Mat m_cloneImg;
    Mat m_grayscaleImg;

    std::vector<Point2f> m_corners;

    void initWindows() {
        // Setup window & sliders
        namedWindow(m_windowName);

        createTrackbar(m_sliderMaxFeatures, m_windowName, nullptr, 500, onSliderUpdate, this);
        createTrackbar(m_sliderMinQuality, m_windowName, nullptr, 10, onSliderUpdate, this);
        createTrackbar(m_sliderMinEuclidDistance, m_windowName, nullptr, 100, onSliderUpdate, this);

        // Initial values
        setTrackbarPos(m_sliderMaxFeatures, m_windowName, 10);
        setTrackbarPos(m_sliderMinQuality, m_windowName, 3);
        setTrackbarPos(m_sliderMinEuclidDistance, m_windowName, 15);
    }

    static void onSliderUpdate(int value, void* param) {
        FeatDetection15* instance = reinterpret_cast<FeatDetection15*>(param);

        int nFeatures = getTrackbarPos(instance->m_sliderMaxFeatures, instance->m_windowName);
        double minQuality = getTrackbarPos(instance->m_sliderMinQuality, instance->m_windowName);
        minQuality = minQuality > 0 ? minQuality / 10 : 0.1f;
        int minEuclidDist = getTrackbarPos(instance->m_sliderMinEuclidDistance, instance->m_windowName);

        // Harris corner detection
        goodFeaturesToTrack(instance->m_grayscaleImg,
                            instance->m_corners,
                            nFeatures,
                            minQuality,
                            minEuclidDist,
                            noArray(),
                            3,
                            true,
                            0.04);

        instance->drawFeatures();
    }

    void drawFeatures() {
        // Revert to original
        m_cloneImg = m_originalImg.clone();

        for (const Point2f& corner : m_corners) {
            std::vector<int> randColors = util::randomInRange(0, 255, 3);
            Scalar color{static_cast<double>(randColors[0]), static_cast<double>(randColors[1]), static_cast<double>(randColors[2])};

            circle(m_cloneImg, corner, 3, color, 3);
        }

        render();
    }

    void render() {
        imshow(m_windowName, m_cloneImg);
    }

public:
    FeatDetection15() : m_originalImg(imread(m_imgPath)) {
        resize(m_originalImg, m_originalImg, Size(), 0.25f, 0.25f);
        m_cloneImg = m_originalImg.clone();
        cvtColor(m_originalImg, m_grayscaleImg, COLOR_BGR2GRAY);

        initWindows();
    }

    void run() {
        render();
        waitKey(0);
    }
};


#endif //GDV_FEATDETECTION15_H
