#ifndef GDV_EDGEDETECTION14_H
#define GDV_EDGEDETECTION14_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class EdgeDetection14 {
private:
    const char* m_imgPath = "../data/images/window01.jpg";
    const char* m_windowName = "Canny edge detection";

    // Slider names
    const char* m_sliderBlur = "slider_blur";
    const char* m_sliderTLower = "slider_t_lower";
    const char* m_sliderTUpper = "slider_t_upper";

    Mat m_originalImg;
    Mat m_img;
    Mat m_imgCanny;
    int m_blurAmount = 3;
    int m_tLower = 30;
    int m_tUpper = 240;

    void render() {
        // Perform blur & Canny edge detection
        blur(m_originalImg, m_img, Size(m_blurAmount, m_blurAmount));
        Canny(m_img, m_imgCanny, m_tLower, m_tUpper);

        // Display images side by side
        Mat resultImg;
        hconcat(m_img, m_imgCanny, resultImg);

        imshow(m_windowName, resultImg);
    }

    void initWindow() {
        // Setup window & sliders
        namedWindow(m_windowName);

        // Pass pointers to the class instance for easy method access
        createTrackbar(m_sliderBlur, m_windowName, nullptr, 30, onSliderUpdate, this);
        createTrackbar(m_sliderTLower, m_windowName, nullptr, 255, onSliderUpdate, this);
        createTrackbar(m_sliderTUpper, m_windowName, nullptr, 255, onSliderUpdate, this);

        setTrackbarPos(m_sliderBlur, m_windowName, m_blurAmount);
        setTrackbarPos(m_sliderTLower, m_windowName, m_tLower);
        setTrackbarPos(m_sliderTUpper, m_windowName, m_tUpper);
    }

    static void onSliderUpdate(int value, void* param) {
        EdgeDetection14* instance = reinterpret_cast<EdgeDetection14*>(param);

        instance->m_blurAmount = getTrackbarPos(instance->m_sliderBlur, instance->m_windowName);
        instance->m_tLower = getTrackbarPos(instance->m_sliderTLower, instance->m_windowName);
        instance->m_tUpper = getTrackbarPos(instance->m_sliderTUpper, instance->m_windowName);

        instance->render();
    }

public:
    EdgeDetection14() {
        m_originalImg = imread(m_imgPath, IMREAD_GRAYSCALE);
        resize(m_originalImg, m_originalImg, Size(), 0.2, 0.2);
        m_img = m_img.clone();

        initWindow();
    }

    void run() {
        render();
        waitKey(0);
    }
};


#endif //GDV_EDGEDETECTION14_H
