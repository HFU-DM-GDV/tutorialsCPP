#ifndef GDV_BLUR09_H
#define GDV_BLUR09_H

#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class Blur09 {
private:
    const char* m_imagePath = "../data/images/Bumbu_Rawon.jpg";

    [[nodiscard]] Mat openCvConvolution(const Mat& img, const Mat& kernel) const {
        Mat result;
        Mat flippedKernel;
        // Flip the kernel as opencv filter2D function is a correlation not a convolution
        flip(kernel, flippedKernel, -1);

        // When ddepth=-1, the output image will have the same depth as the source
        int ddepth = -1;
        filter2D(img, result, ddepth, flippedKernel);

        return result;
    }

    void showKernel(const Mat& kernel) const {
        const char* windowTitle = "Kernel";
        Mat img;

        // Scale kernel to make it visually more appealing
        normalize(kernel, img, 0, 255, NORM_MINMAX, CV_8UC3);

        namedWindow(windowTitle, WINDOW_NORMAL);
        resizeWindow(windowTitle, Size(300, 300));

        imshow(windowTitle, img);
    }

    void showResults(const Mat& img, const Mat& result) const {
        imshow("Original", img);
        imshow("Resulting", result);

        waitKey(0);
    }

public:
    Blur09() = default;

    void run() {
        Mat img = imread(m_imagePath, IMREAD_GRAYSCALE);

        // Define kernel size
        int kernelSize = 50;

        // Define Gaussian standard deviation (sigma)
        int sigma = 6;

        // Create the kernel
        Mat kernel1d = getGaussianKernel(kernelSize, sigma);

        Mat transposedKernel;
        transpose(kernel1d, transposedKernel);

        Mat kernel2d = kernel1d * transposedKernel;

        // Visualize the kernel
        showKernel(kernel2d);

        // Run convolution and measure the time it takes
        auto startTime = std::chrono::steady_clock::now();
        Mat result = openCvConvolution(img, kernel2d);
        auto endTime = std::chrono::steady_clock::now();
        auto diff = endTime - startTime;

        std::cout << "Convolution took " << std::chrono::duration<double, std::milli>(diff).count() << "ms." << std::endl;

        showResults(img, result);
    }
};


#endif //GDV_BLUR09_H
