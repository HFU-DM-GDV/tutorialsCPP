#ifndef GDV_CONNECTEDCOMPONENTS07_H
#define GDV_CONNECTEDCOMPONENTS07_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class ConnectedComponents07 {
private:
    const char* m_imagePath = "../data/images/smarties01.JPG";
    uint8_t m_hue;
    uint8_t m_hueRange;
    uint8_t m_saturation;
    uint8_t m_saturationRange;
    uint8_t m_value;
    uint8_t m_valueRange;

    Vec3b m_lowerRange;
    Vec3b m_upperRange;

    Scalar m_markerColor{0, 0, 255};

    void computeColorRanges() {
        m_lowerRange = {(uint8_t)(m_hue - m_hueRange), (uint8_t)(m_saturation - m_saturationRange), (uint8_t)(m_value - m_valueRange)};
        m_upperRange = {(uint8_t)(m_hue + m_hueRange), (uint8_t)(m_saturation + m_saturationRange), (uint8_t)(m_value + m_valueRange)};
    }

    void closing(Mat& img, Size2i kernelSize, MorphShapes shape) {
        Mat kernel = getStructuringElement(shape, kernelSize);
        morphologyEx(img, img, MORPH_CLOSE, kernel, Point(-1, -1), 20);
    }

public:
    ConnectedComponents07(uint8_t hue, uint8_t hueRange, uint8_t saturation, uint8_t saturationRange, uint8_t value, uint8_t valueRange) :
        m_hue(hue), m_hueRange(hueRange), m_saturation(saturation), m_saturationRange(saturationRange), m_value(value), m_valueRange(valueRange) {
        computeColorRanges();
    }

    // Default constructor with green in HSV
    ConnectedComponents07() : ConnectedComponents07(60, 10, 155, 100, 155, 100) {}

    void run() {
        // Load image
        Mat img = imread(m_imagePath);
        resize(img, img, Size(800, 600));

        // Convert to HSV
        Mat imgHsv;
        cvtColor(img, imgHsv, COLOR_BGR2HSV);

        // Create a mask
        Mat mask;
        inRange(imgHsv, m_lowerRange, m_upperRange, mask);

        // Modify the mask image with dilation or erosion
        // in order to avoid very small connected components
        closing(mask, Size(5, 5), MORPH_ELLIPSE);

        // Find connected components
        Mat labels;
        Mat stats;
        Mat centroids;
        int nLabels = connectedComponentsWithStats(mask, labels, stats, centroids);

        // Loop over all (reasonable) found connected components
        // Start with 1, index 0 is always the background
        for (int i = 1; i < nLabels; i++) {
            // Bounding box x, y start
            int x = stats.at<int>(i, CC_STAT_LEFT);
            int y = stats.at<int>(i, CC_STAT_TOP);

            // Bounding box width and height
            int width = stats.at<int>(i, CC_STAT_WIDTH);
            int height = stats.at<int>(i, CC_STAT_HEIGHT);

            // Centroids x, y
            int x_centroid = (int) centroids.at<double>(i, 0);
            int y_centroid = (int) centroids.at<double>(i, 1);

            // Find and draw center
            circle(img, Point(x_centroid, y_centroid), 7, m_markerColor, -1);

            // Find and draw bounding box
            rectangle(img, Point(x, y), Point(x + width, y + height), m_markerColor, 3);
        }

        // Show the original image with drawings in one window
        imshow("Original image", img);

        // Show the mask image in another window
        imshow("Mask image", mask);

        waitKey(0);
        destroyAllWindows();
    }
};


#endif //GDV_CONNECTEDCOMPONENTS07_H
