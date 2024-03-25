#ifndef GDV_PIXELMANIPULATION02_H
#define GDV_PIXELMANIPULATION02_H

#include <format>
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class PixelManipulation02 {
private:
    const char* path = "../data/images/nl_clown.jpg";
public:
    PixelManipulation02() = default;

    void run() const {
        // TODO Loading images in grey and color
        Mat imgColor = imread(path, IMREAD_COLOR);
        Mat imgColorCopy = imgColor.clone();
        Mat imgGray = imread(path, IMREAD_GRAYSCALE);

        // TODO Do some print out about the loaded data using type, dtype and shape
        std::cout << std::format("Data type: {} Dimensions: {}x{}", imgColor.type(), imgColor.rows, imgColor.cols) << std::endl;

        // TODO Extract the size or resolution of the image (Grayscale)
        int width = imgColor.cols;
        int height = imgColor.rows;

        // TODO Resize image
        Mat resizedImg;
        resize(imgGray, resizedImg, Size(64, 64));

        // TODO Print first row
        std::cout << resizedImg.row(0) << std::endl;

        // TODO Print first column
        std::cout << resizedImg.col(0) << std::endl;

        // TODO Set an area of the image to black (Colored image)
        Rect roi(0, 40, width, 20);
        Mat area = imgColor(roi);
        area.setTo(Scalar(0, 0, 0));

        // TODO Show the image and wait until key pressed
        imshow("Black bar", imgColor);

        // TODO Find all used colors in the image
        std::unordered_set<int> uniqueColors;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Vec3b color = imgColor.at<Vec3b>(y, x);
                int uniqueColor = (color[0] << 16) + (color[1] << 8) + color[2];
                uniqueColors.insert(uniqueColor);
            }
        }

        std::cout << "Unique colors: " << uniqueColors.size() << std::endl;

        // TODO Copy one part of an image into another one
        Mat copyRoi = imgColor(Rect(0, 100, width, 20)).clone(); // Deep copy
        copyRoi.copyTo(imgColor(Rect(0, 0, width, 20)));

        // TODO Save image to a file
        imwrite("../out/result_pixel_manip.jpg", imgColor);

        // TODO Show the image again
        imshow("Image part copied", imgColor);

        // TODO Show the original image (copy demo)
        imshow("Image original", imgColorCopy);

        waitKey(0);
    }
};


#endif //GDV_PIXELMANIPULATION02_H
