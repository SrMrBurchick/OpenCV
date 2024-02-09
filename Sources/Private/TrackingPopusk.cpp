#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <cstdio>

int main() {
    cv::Ptr<cv::Tracker> Tracker = cv::TrackerMIL::create();
    cv::VideoCapture Video(VIDEO_PATH);

    if (!Video.isOpened()) {
        printf("Tobi Pizda!");
        return -1;
    }

    cv::Mat Frame;
    Video.read(Frame);

    cv::Rect BBox(60, 750, 300, 300);

    Tracker->init(Frame, BBox);

    do {

        bool bIsTracking = Tracker->update(Frame, BBox);
        if (bIsTracking) {
            cv::rectangle(Frame, BBox, cv::Scalar(255, 0, 0), 2, 1);
        }

        cv::imshow("Popusk Tracking", Frame);

        int K = cv::waitKey(1);

        if (K == 27) {
            break;
        }
    } while (Video.read(Frame));


    return 0;
}
