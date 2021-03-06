#ifndef OPENCV_HELPERS_H
#define OPENCV_HELPERS_H

#include <iostream>

using std::cout; using std::endl;

/**
OpenCV helper functions for Flitr:
    -Conversion between flitr::Image and cv::Mat image
    -Conversion between flitr::ImageFormat format and cv::type formats

*/

#ifdef FLITR_USE_OPENCV
    #include <opencv2/core/core.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
    using namespace cv;
#endif

#include <flitr/image_processor.h>


namespace flitr {

    class OpenCVHelperFunctions{
    public:

        /** Get openCV format from FLitr ImageFormat */
        int getOpenCVFormat(flitr::ImageFormat::PixelFormat pixelFormat);

        /** Copy Flitr image to OpenCV image */
        Mat copyToOpenCVimage(std::vector<Image**> sourceFlitr, ImageFormat imFormat);
        /** Copy OpenCV image to flitr */
        void copyToFlitrImage(Mat &sourceOpenCV, std::vector<Image**> destFlitr, ImageFormat imFormat);

        /** Assign flitr image to an OpenCV.data()*/
        Mat assignToOpenCVimage(std::vector<Image**> sourceFlitr, ImageFormat imFormat);
    };
}


#endif
