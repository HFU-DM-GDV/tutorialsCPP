#ifndef GDV_VIDEOCAM03_H
#define GDV_VIDEOCAM03_H

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "util.h"

using namespace cv;

class VideoCam03 {
private:
    const char* title = "Videocapture";
public:
    VideoCam03() = default;

    void run() const {
        // Capture webcam image
        Mat img;
        VideoCapture cap(0);

        cap >> img;

        // Get camera image parameters from get()
        double width = cap.get(CAP_PROP_FRAME_WIDTH);
        double height = cap.get(CAP_PROP_FRAME_HEIGHT);
        int type = img.type();
        double codecId = cap.get(CAP_PROP_CODEC_PIXEL_FORMAT);

        int insertRegionWidth = (int) width / 2;
        int insertRegionHeight = (int) height / 2;

        // Create a window for the video
        namedWindow(title, WINDOW_FREERATIO);
        // Start a loop
        while (true) {
            // (In loop) read a camera frame and check if that was successful
            cap >> img;

            if (img.empty()) {
                std::cerr << "Failed to grab image" << std::endl;
            }

            // (In loop) create four flipped tiles of the image
            Mat emptyImg{img.size(), type};

            Mat srcResized = img.clone();
            resize(srcResized, srcResized, Size(insertRegionWidth, insertRegionHeight));

            // Original
            util::copyToImgRegion(emptyImg, srcResized, 0, 0, insertRegionWidth, insertRegionHeight);

            // Bottom left flip horizontally
            Mat blhFlip = srcResized.clone();
            flip(blhFlip, blhFlip, 0);
            util::copyToImgRegion(emptyImg, blhFlip, insertRegionWidth, 0, insertRegionWidth, insertRegionHeight);

            // Bottom left flip horizontally & vertically
            Mat blhvFlip = srcResized.clone();
            flip(blhvFlip, blhvFlip, -1);
            util::copyToImgRegion(emptyImg, blhvFlip, 0, insertRegionHeight, insertRegionWidth, insertRegionHeight);

            // Top right flip vertically
            Mat trvFlip = srcResized.clone();
            flip(trvFlip, trvFlip, 1);
            util::copyToImgRegion(emptyImg, trvFlip, insertRegionWidth, insertRegionHeight, insertRegionWidth, insertRegionHeight);

            // (In loop) display the image
            imshow(title, emptyImg);

            // (In loop) press q to close the window and exit the loop
            // ASCII Code for q
            if (waitKey(1) == 113) {
                break;
            }
        }

        // Release the video capture object and window
        destroyWindow(title);
        cap.release();
    }
};


#endif //GDV_VIDEOCAM03_H
