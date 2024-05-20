#ifndef GDV_PROJTRANSFORMATION_H
#define GDV_PROJTRANSFORMATION_H

#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class ProjTransformation13 {
private:
    const char* m_imgPath = "../data/images/nl_clown.jpg";
    const char* m_originalWindowTitle = "Original image";
    const char* m_transformWindowTitle = "Transformed image";

    static inline std::vector<Point2f> m_sourcePoints{};
    static inline std::vector<Point2f> m_destPoints{};

    Mat m_originalImg;
    int m_originalWidth{};
    int m_originalHeight{};

    Mat m_selectionImg;
    Mat m_transformImg;

    bool m_computationDone = false;

    // Event handlers
    static void onClickSource(int event, int x, int y, int flags, void* param) {
        if (event != EVENT_LBUTTONDBLCLK || m_sourcePoints.size() == 4) {
            return;
        }

        Mat* selectionImg = reinterpret_cast<Mat*>(param);
        // If the left mouse button was clicked, add the point to the source array
        m_sourcePoints.emplace_back(x, y);

        // Draw a circle around the clicked point
        circle(*selectionImg, Point(x, y), 7, Scalar(0, 0, 255), 2);
    }

    static void onClickDest(int event, int x, int y, int flags, void* param) {
        if (event != EVENT_LBUTTONDBLCLK || m_destPoints.size() == 4) {
            return;
        }

        Mat* transformImg = reinterpret_cast<Mat*>(param);
        // If the left mouse button was clicked, add the point to the dest array
        m_destPoints.emplace_back(x, y);

        // Draw a circle around the clicked point
        circle(*transformImg, Point(x, y), 7, Scalar(0, 0, 255), 2);
    }

    // Init
    void initImages() {
        // Load image and resize for better display
        m_originalImg = imread(m_imgPath);
        resize(m_originalImg, m_originalImg, Size(400, 400), 0, 0, INTER_CUBIC);

        m_originalWidth = m_originalImg.cols;
        m_originalHeight = m_originalImg.rows;

        m_selectionImg = m_originalImg.clone();
        m_transformImg = Mat::zeros(m_originalHeight, m_originalWidth, CV_8UC3);
    }

    void setupWindows() {
        namedWindow(m_originalWindowTitle);
        setMouseCallback(m_originalWindowTitle, onClickSource, &m_selectionImg);

        namedWindow(m_transformWindowTitle);
        setMouseCallback(m_transformWindowTitle, onClickDest, &m_transformImg);
    }


public:
    ProjTransformation13() {
        initImages();
        setupWindows();
    }

    [[noreturn]] void run() {
        while (true) {
            if (!m_computationDone && m_sourcePoints.size() == 4 && m_destPoints.size() == 4) {
                Mat transformMat = getPerspectiveTransform(m_sourcePoints, m_destPoints);
                warpPerspective(m_originalImg, m_transformImg, transformMat, Size(m_originalWidth, m_originalHeight));
                m_computationDone = true;
            }

            char key = (char) waitKey(10);

            if (key == 'r') {
                m_sourcePoints.clear();
                m_destPoints.clear();
                m_computationDone = false;
                m_selectionImg = m_originalImg.clone();
                m_transformImg = Mat::zeros(m_originalHeight, m_originalWidth, CV_8UC3);
            } else if (key == 'q') {
                break;
            }

            imshow(m_originalWindowTitle, m_selectionImg);
            imshow(m_transformWindowTitle, m_transformImg);
        }

        destroyAllWindows();
    }
};


#endif //GDV_PROJTRANSFORMATION_H
