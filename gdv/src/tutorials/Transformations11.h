#ifndef GDV_TRANSFORMATIONS11_H
#define GDV_TRANSFORMATIONS11_H

#include <cmath>
#include <numbers>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../util.h"

using namespace cv;

class Transformations11 {
private:
    const char* m_imagePath = "../data/images/nl_clown.jpg";
    Mat m_img;
    int m_height;
    int m_width;

    Mat m_translatedImg;
    Mat m_anisoScaledImg;
    Mat m_clockwiseRotImg;
    Mat m_counterclockwiseRotImg;

    static Mat generateTranslationMatrix(int x, int y) {
        return util::generateTransformationMatrix({
            1.0f, 0.0f, (float)x,
            0.0f, 1.0f, (float)y
        });
    }

    static Mat generateAnisoScalingMatrix(float xScale, float yScale) {
        return util::generateTransformationMatrix({
            xScale, 0.0f,   0.0f,
            0.0f,   yScale, 0.0f
        });
    }

    static Mat generateRotationMatrix(float angleDeg) {
        float angleRad =  (std::numbers::pi / 180.0f) * angleDeg;

        return util::generateTransformationMatrix({
            std::cos(angleRad), -std::sin(angleRad), 0,
            std::sin(angleRad), std::cos(angleRad), 0
        });
    }

    void computeTransforms() {
        // Translation x: 100, y: 50
        warpAffine(m_img, m_translatedImg, generateTranslationMatrix(100, -50), Size(m_width + 100, m_height + 50));

        // Anisotropic scaling that stretches to double length horizontally and squeezes vertically to the half height
        warpAffine(m_img, m_anisoScaledImg, generateAnisoScalingMatrix(2.0f, 0.5f), Size(m_width * 2, (int)(m_height * 0.5)));

        // 45° clockwise rotation
        warpAffine(m_img, m_clockwiseRotImg, generateRotationMatrix(-45.0f), Size(m_width, m_height));

        // 45° counterclockwise rotation around center
        Mat rotMat = getRotationMatrix2D(Point((m_width - 1) / 2, (m_height - 1) / 2), 45, 1);
        warpAffine(m_img, m_counterclockwiseRotImg, rotMat, Size(m_width, m_height));
    }

    void showResults() {
        imshow("Original", m_img);
        imshow("Translation", m_translatedImg);
        imshow("Anisotropic Scaling", m_anisoScaledImg);
        imshow("45deg clockwise rotation", m_clockwiseRotImg);
        imshow("45deg counterclockwise rotation around center", m_counterclockwiseRotImg);
    }
public:
    constexpr static const float ROT_ANGLE = 45.0f;

    Transformations11() {
        // Load image and resize for better display
        m_img = imread(m_imagePath);
        resize(m_img, m_img, Size(400, 400), INTER_CUBIC);

        m_height = m_img.rows;
        m_width = m_img.cols;
    }

    void run() {
        computeTransforms();
        showResults();
        waitKey(0);
        destroyAllWindows();
    }
};


#endif //GDV_TRANSFORMATIONS11_H
