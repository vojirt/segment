#include "segment.h"

double kernelProfile_Epanechnikov(double x)
{ return (x <= 1) ? (2.0/3.14)*(1-x) : 0; }

int main(int argc, char ** argv)
{

    if (argc < 6){
        std::cout << "Usage: segment <image> [int]x1 [int]y1 [int]x2 [int]y2 [int]apriori" << std::endl;
        std::cout << "      where (x1,y1) is top-left corner and (x2, y2) is bottom-right corner" << std::endl;
        std::cout << "      apriori set a flag to use Epanechnikov kernel weighting as an apriori for the object pixels inside the bbox" << std::endl;
        return 0;
    }

    cv::Mat img = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    int x1 = atoi(argv[2]);
    int y1 = atoi(argv[3]);
    int x2 = atoi(argv[4]);
    int y2 = atoi(argv[5]);

    std::vector<cv::Mat> imgChannels;
    //cv::Mat ra[3] = {im1, im2, im3};
    cv::split(img, imgChannels);

    double time_profile_counter = cv::getCPUTickCount();
//    std::pair<cv::Mat, cv::Mat> probs;
//    for (int i =0; i < 1000; ++i)
//        probs = Segment::computePosteriors(imgChannels, x1, y1, x2, y2, cv::Mat(), cv::Mat(), cv::Mat(), Histogram(), 8);

    cv::Mat fgWeight(img.rows, img.cols, CV_64FC1);
    cv::Mat bgWeight(img.rows, img.cols, CV_64FC1);

    std::pair<cv::Mat, cv::Mat> probs;

    if (argc > 6 && atoi(argv[6]) > 0){
        fgWeight.setTo(0.0);
        //weights are epanechnikov distr. with peek at the center of the image;
        double cx = x1 + (x2-x1)/2.;
        double cy = y1 + (y2-y1)/2.;
        double kernelSize_width = 1.0/(0.5*static_cast<double>(x2-x1)*1.4142+1);  //sqrt(2)
        double kernelSize_height = 1.0/(0.5*static_cast<double>(y2-y1)*1.4142+1);

        for (int y = y1; y < y2+1; ++y){
            double * weightPtr = fgWeight.ptr<double>(y);
            double tmp_y = std::pow((cy-y)*kernelSize_height, 2);
            for (int x = x1; x < x2+1; ++x){
                weightPtr[x] = kernelProfile_Epanechnikov(std::pow((cx-x)*kernelSize_width,2) + tmp_y);
            }
        }
        bgWeight = cv::Mat::ones(img.rows, img.cols, CV_64FC1) - fgWeight;
    
        probs = Segment::computePosteriors(imgChannels, x1, y1, x2, y2, cv::Mat(), fgWeight, bgWeight, Segment::Histogram(), 8);
    }else{
        probs = Segment::computePosteriors(imgChannels, x1, y1, x2, y2, cv::Mat(), cv::Mat(), cv::Mat(), Segment::Histogram(), 8);
    }


    time_profile_counter = cv::getCPUTickCount() - time_profile_counter;
    std::cout << "Segmentation in " << time_profile_counter/((double)cvGetTickFrequency()*1000)  << " ms." << std::endl;

    cv::Mat mask(probs.first.rows, probs.first.cols, CV_8UC1);
    probs.first.convertTo(probs.first, CV_32F);
    probs.second.convertTo(probs.second, CV_32F);
    cv::threshold(probs.first/probs.second, mask, 1, 255, cv::THRESH_BINARY);
    cv::Mat wholeMask(img.rows, img.cols, CV_8UC1);
    wholeMask.setTo(0);
    mask.copyTo(wholeMask(cv::Rect(x1, y1, x2-x1, y2-y1)));
    cv::Mat wholeMask2(img.rows, img.cols, CV_8UC1);
    wholeMask2.setTo(0);
    cv::threshold(probs.second/probs.first, mask, 1, 255, cv::THRESH_BINARY);
    mask.copyTo(wholeMask2(cv::Rect(x1, y1, x2-x1, y2-y1)));

    imgChannels[2] = 0.7*wholeMask + imgChannels[2];
    imgChannels[0] = 0.7*wholeMask2 + imgChannels[0];
    cv::merge(imgChannels, img);

    cv::imshow("foreground Mask", wholeMask);
    cv::imshow("background Mask", wholeMask2);
    cv::imshow("img", img);
    //cv::imshow("Background posterior", probs.second);
    cv::waitKey();

    return 0;
}
