#include "opencv2/opencv.hpp"
#include "opencv2/ximgproc/segmentation.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/tracking/tracking.hpp"
#include "opencv2/core/ocl.hpp"
#include <ctime>
#include <cstdio>

int main() {

    cv::setUseOptimized(true);
    cv::setNumThreads(4);

    cv::Mat Image;
    Image = cv::imread(IMAGE_PATH);

    if (Image.data == nullptr) {
        printf("Filed to find file %s\n", IMAGE_PATH);
    }

    int NewImageHeight = 200;
    int NewImageWidth = Image.cols * NewImageHeight / Image.rows;
    cv::resize(Image, Image, cv::Size(NewImageWidth, NewImageHeight));

    cv::Ptr<cv::ximgproc::segmentation::SelectiveSearchSegmentation> SelectiveSearch = cv::ximgproc::segmentation::createSelectiveSearchSegmentation();
    SelectiveSearch->setBaseImage(Image);
    // SelectiveSearch->switchToSelectiveSearchQuality();
    SelectiveSearch->switchToSelectiveSearchFast();

    std::vector<cv::Rect> Rects;
    SelectiveSearch->process(Rects);
    printf("Total Number of Region Proposals: %d\n", (int)Rects.size());

    int NumShowRect = 100;
    int Increment = 50;

    while (true) {
        cv::Mat ImageOut = Image.clone();

        for(int i = 0; i < Rects.size(); ++i) {
            if (i < NumShowRect) {
                cv::rectangle(ImageOut, Rects[i], cv::Scalar(0, 255, 0));
            } else {
                break;
            }
        }

        cv::imshow("Output", ImageOut);

        int K = cv::waitKey();

        if (K == 109) {
            NumShowRect += Increment;
        } else if (K == 108 && NumShowRect > Increment) {
            NumShowRect -= Increment;
        } else if (K == 113) {
            break;
        }
    }

    return 0;
}
