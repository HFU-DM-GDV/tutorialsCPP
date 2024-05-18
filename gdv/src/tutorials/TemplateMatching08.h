#ifndef GDV_TEMPLATEMATCHING08_H
#define GDV_TEMPLATEMATCHING08_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class TemplateMatching08 {
private:
    const char* m_imagePath = "../data/images/chewing_gum_balls09.jpg";
    const char* m_templateImagePath = "../data/images/cgb_yelllow.jpg";

public:
    TemplateMatching08() = default;

    void run() {
        Mat img = imread(m_imagePath);
        Mat templateImg = imread(m_templateImagePath);

        int templateWidth = templateImg.cols;
        int templateHeight = templateImg.rows;

        imshow("Original image", img);

        // Define template matching methods
        std::vector<TemplateMatchModes> methods = {TM_CCOEFF, TM_CCOEFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_SQDIFF, TM_SQDIFF_NORMED};

        // Loop over all methods in order to compare them
        for (TemplateMatchModes method : methods) {
            // Work on a new image each time
            Mat imgCopy = img.clone();
            Mat result;

            // Do the template matching
            matchTemplate(imgCopy, templateImg, result, method);

            double minVal;
            double maxVal;
            Point minLoc;
            Point maxLoc;
            Point loc;

            // Get the best match location
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

            switch (method) {
                case TM_SQDIFF:
                case TM_SQDIFF_NORMED:
                    loc = minLoc;
                    break;
                default:
                    loc = maxLoc;
            }

            // Draw rectangle at found location
            rectangle(imgCopy, loc, Point(loc.x + templateWidth, loc.y + templateHeight), Scalar(0, 0, 255));

            // Show original image with found location
            imshow("Location", imgCopy);

            waitKey(0);
        }

        destroyAllWindows();
    }
};


#endif //GDV_TEMPLATEMATCHING08_H
