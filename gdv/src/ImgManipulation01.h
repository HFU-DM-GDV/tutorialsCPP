#ifndef GDV_IMGMANIPULATION01_H
#define GDV_IMGMANIPULATION01_H

// First step is to import the opencv module which is called 'cv2' - Basic includes
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class ImgManipulation01 {
public:
    ImgManipulation01() = default;

    void run() const {
        // TODO Check the opencv version
        std::cout << "Version: " << CV_VERSION << std::endl;

        // TODO Load an image with image reading modes using 'imread'
        Mat img = imread( "../data/images/logo.png"); // additional flags: IMREAD_GRAYSCALE, IMREAD_..

        imshow("Unchanged image", img);

        // TODO Resize image with 'resize'
        Mat resizedImg;
        resize(img, resizedImg, Size(), 0.5, 0.5);
        imshow("Resized image", resizedImg);

        // TODO Rotate image (but keep it rectangular) with 'rotate'
        Mat rotatedImg;
        rotate(img, rotatedImg, ROTATE_90_CLOCKWISE);
        imshow("Rotated image", rotatedImg);

        // TODO Save image with 'imwrite'
        imwrite("../out/result.png", rotatedImg);

        // Keep the window(s) open
        waitKey(0);
    }
};

#endif //GDV_IMGMANIPULATION01_H
