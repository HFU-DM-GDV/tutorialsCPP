#ifndef GDV_VIDEOFILE04_H
#define GDV_VIDEOFILE04_H

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "util.h"

using namespace cv;

class VideoFile04 {
private:
    const char* title = "Video file";
public:
    VideoFile04() = default;

    void run() const {
        // Open a video file
        VideoCapture cap("../data/videos/hello_UH.m4v");

        // Get camera image parameters from get()
        double width = cap.get(CAP_PROP_FRAME_WIDTH);
        double height = cap.get(CAP_PROP_FRAME_HEIGHT);

        int insertRegionWidth = (int) width / 2;
        int insertRegionHeight = (int) height / 2;

        namedWindow(title);

        // Start a loop
        while (true) {
            // (In loop) read one video frame
            Mat frame;
            cap >> frame;

            if (frame.empty()) {
                break;
            }

            // (In loop) create four tiles of the image
            Mat emptyFrame{frame.size(), frame.type()};

            // (In loop) show the image
            Mat frameResized = frame.clone();
            resize(frameResized, frameResized, Size(insertRegionWidth, insertRegionHeight));

            // Original
            util::copyToImgRegion(emptyFrame, frameResized, 0, 0, insertRegionWidth, insertRegionHeight);

            // Bottom left flip horizontally
            Mat blhFlip = frameResized.clone();
            flip(blhFlip, blhFlip, 0);
            util::copyToImgRegion(emptyFrame, blhFlip, insertRegionWidth, 0, insertRegionWidth, insertRegionHeight);

            // Bottom left flip horizontally & vertically
            Mat blhvFlip = frameResized.clone();
            flip(blhvFlip, blhvFlip, -1);
            util::copyToImgRegion(emptyFrame, blhvFlip, 0, insertRegionHeight, insertRegionWidth, insertRegionHeight);

            // Top right flip vertically
            Mat trvFlip = frameResized.clone();
            flip(trvFlip, trvFlip, 1);
            util::copyToImgRegion(emptyFrame, trvFlip, insertRegionWidth, insertRegionHeight, insertRegionWidth, insertRegionHeight);

            imshow(title, emptyFrame);

            // (In loop) close the window and stop the loop if 'q' is pressed
            // ASCII Code for q
            if (waitKey(1) == 113) {
                break;
            }
        }
        // Release the video and close all windows
        cap.release();
        destroyWindow(title);
    }
};


#endif //GDV_VIDEOFILE04_H
