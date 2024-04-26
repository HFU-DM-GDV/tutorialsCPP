#ifndef GDV_RGBTOHSV06_H
#define GDV_RGBTOHSV06_H

#include <iostream>
#include <format>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class RgbToHsv06 {
private:
    const char* mainWindowTitle = "Cam";

    // Enter some default values and uncomment
    uint8_t m_hueRange = 20;
    uint8_t m_saturationRange = 20;
    uint8_t m_valueRange = 20;

    Mat m_frame;

    // Callback to pick the color on double click
    static void colorPicker(int event, int x, int y, int flags, void* param) {
        if (event != EVENT_LBUTTONDBLCLK) {
            return;
        }

        Mat* frame = reinterpret_cast<Mat*>(param);
        Vec3b color = frame->at<Vec3b>(y, x);

        Mat bgrPixel{1, 1, CV_8UC3, color};
        Mat hsvPixel;

        cvtColor(bgrPixel, hsvPixel, COLOR_BGR2HSV);

        Vec3b convertedColor = hsvPixel.at<Vec3b>(0, 0);
        hue = convertedColor[0];
        saturation = convertedColor[1];
        value = convertedColor[2];
    }

public:
    static inline uint8_t hue = 50;
    static inline uint8_t saturation = 80;
    static inline uint8_t value = 80;
    static const int FONT = FONT_HERSHEY_SIMPLEX;
    constexpr static const double FONT_SIZE = 0.6;
    static inline const Scalar COLOR{0, 255, 255};

    RgbToHsv06() {
        namedWindow(mainWindowTitle);
        setMouseCallback(mainWindowTitle, colorPicker, &m_frame);
    }

    void run() {
        VideoCapture cap{0};
        cap >> m_frame;

        while (true) {
            cap >> m_frame;

            if (m_frame.empty()) {
                break;
            }

            // Copy image to draw on
            Mat img = m_frame.clone();

            // Compute color ranges for display
            Vec3b lowerRange{(uint8_t)(hue - m_hueRange), (uint8_t)(saturation - m_saturationRange), (uint8_t)(value - m_valueRange)};
            Vec3b upperRange{(uint8_t)(hue + m_hueRange), (uint8_t)(saturation + m_saturationRange), (uint8_t)(value + m_valueRange)};

            // Compute selected color in BGR
            Mat hsvColor{1, 1, CV_8UC3, Vec3b{hue, saturation, value}};
            Mat bgrColor;

            cvtColor(hsvColor, bgrColor, COLOR_HSV2BGR);

            // Draw selection color circle
            circle(img, Point{140, 45}, 15, bgrColor.at<Vec3b>(0, 0), 30);
            putText(img, std::format("Hue: {}", hue), Point{0, 25}, FONT, FONT_SIZE, COLOR);
            putText(img, std::format("Sat: {}", saturation), Point{0, 50}, FONT, FONT_SIZE, COLOR);
            putText(img, std::format("Value: {}", value), Point{0, 75}, FONT, FONT_SIZE, COLOR);

            // Convert to HSV
            Mat hsvFrame;
            cvtColor(m_frame, hsvFrame, COLOR_BGR2HSV);

            // Create a bitwise mask
            Mat mask;
            inRange(hsvFrame, lowerRange, upperRange, mask);

            // Apply mask
            Mat result;
            bitwise_and(m_frame, m_frame, result, mask);

            // Show the original image with drawings in one window
            imshow(mainWindowTitle, img);

            // Show the masked image in another window
            imshow("Mask", mask);

            // Show the masked image in another window
            imshow("Masked", result);

            if (waitKey(10) == 113) {
                break;
            }
        }
    }
};


#endif //GDV_RGBTOHSV06_H
