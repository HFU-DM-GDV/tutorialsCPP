#ifndef GDV_WEBCAMDRAW05_H
#define GDV_WEBCAMDRAW05_H

#include <iostream>
#include <utility>
#include <numbers>
#include <cmath>
#include <chrono>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class WebcamDraw05 {
private:
    const char *title = "Webcam draw";
    float time = 0.0f;
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    // Create a function and a timer variable for the moving rectangle
    [[nodiscard]] std::pair<int, int> calculatePos(float t, int centerX, int centerY, int radius) const {
        double rads = t * (2 * std::numbers::pi / (ROTATION_TIME * 1000));
        int x = (int) (radius * std::cos(rads)) + centerX;
        int y = (int) (radius * std::sin(rads)) + centerY;

        return {x, y};
    }

    void drawAnimatedRectangle(Mat& frame, Point p1, int width, int height, Scalar color, int thickness, int offset, float t) const {
        // The rectangle moves in a circular path, calculate the initial circle center
        // We use the first corner as reference
        int centerX = p1.x - offset;
        int centerY = p1.y - offset;

        auto currPos = calculatePos(t, centerX, centerY, offset);
        Point topLeftCorner{currPos.first, currPos.second};
        Point bottomRightCorner{currPos.first + width, currPos.second + height};

        rectangle(frame, topLeftCorner, bottomRightCorner, color, thickness);
    }

public:
    WebcamDraw05() = default;
    static const int FRAME_TIME = 1;
    static const int ROTATION_TIME = 5; // Time in seconds for a full rotation

    void run() {
        VideoCapture cap{0};

        // Capture webcam image
        Mat frame;
        cap >> frame;

        // Get camera image parameters from get()
        int width = cap.get(CAP_PROP_FRAME_WIDTH);
        int height = cap.get(CAP_PROP_FRAME_HEIGHT);

        namedWindow(title);

        // Create helper variables for drawing and writing text
        // Thickness
        int thin = 2;
        int thick = 5;

        // Color
        Scalar color{255, 0, 0}; // Blue, BGR

        // Fonts
        int fontSizeBig = 3;
        int fontSizeSmall = 1;

        // Start a loop
        while (true) {
            // (In loop) capture the image
            cap >> frame;

            // (In loop) check if capture succeeded
            if (frame.empty()) {
                break;
            }

            // (In loop) draw a blue diagonal cross over the image
            line(frame, Point(0, 0), Point(width, height), color, thick);
            line(frame, Point(width, 0), Point(0, height), color, thick);

            // (In loop) draw a circle
            circle(frame, Point(width / 2, height / 2), 100, Scalar(0, 255, 0), thin);

            // (In loop) write some text
            putText(frame, "Hello OpenCV", Point(50, 100), FONT_HERSHEY_SIMPLEX, fontSizeSmall, Scalar(0, 0, 255), thin);

            // (In loop) draw arrows
            arrowedLine(frame, Point(50, 200), Point(200, 200), Scalar(0, 0, 255), thick);
            arrowedLine(frame, Point(50, 300), Point(200, 300), Scalar(0, 255, 0), thick);

            // (In loop) draw a rectangle that moves on a circular path
            drawAnimatedRectangle(frame, Point(250, 250), 100, 50, color, thin, 50, time);

            // (In loop) display the image
            imshow(title, frame);

            // (In loop) press q to close the window
            // ASCII Code for q
            if (waitKey(FRAME_TIME) == 113) {
                break;
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            time += duration.count();

            startTime = endTime;
        }
        // Release the video capture object and window
        destroyWindow(title);
        cap.release();
    }
};


#endif //GDV_WEBCAMDRAW05_H
