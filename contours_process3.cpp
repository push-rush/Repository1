#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;

int iLowH = 100, iHighH = 124, iLowS = 43, iHighS = 245, iLowV = 50, iHighV = 245;
void Color_distinguish(Mat frame, Mat imgHSV, Mat imgThresholded, Mat imgCanny,  Mat element);
int main(int argc, char** argv)
{
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        cout<< "openning failed!" <<endl;
        return 1;
    }
    
    while(1)
    {
        Mat frame;
        cap >> frame;
        if(frame.empty())
        {
            cout<< "frame off!" <<endl;
            break;
        }
        Mat imgHSV, imgThresholded, imgCanny, element;
        Color_distinguish(frame, imgHSV, imgThresholded, imgCanny, element);

        waitKey(30);
    }
    cap.release();
}
void Color_distinguish(Mat frame, Mat imgHSV, Mat imgThresholded, Mat imgCanny,  Mat element)
{
    resize(frame, frame, Size(320,240), 0, 0, INTER_AREA);

    //createTrackbar
    namedWindow("Color",WINDOW_NORMAL);
    namedWindow("video",WINDOW_NORMAL);

    createTrackbar("LowH", "Color", &iLowH, 180); //Hue(0 - 179);
    createTrackbar("HighH", "Color", &iHighH, 180); 
    createTrackbar("LowS", "Color", &iLowS, 255); //Sarturation(0 - 255);
    createTrackbar("HighS", "Color", &iHighS, 255); 
    createTrackbar("LowV", "Color", &iLowV, 255); //Value(0 - 255);
    createTrackbar("HighV", "Color", &iHighV, 255);

    //cvtColor
    cvtColor(frame, imgHSV, COLOR_BGR2HSV);

    //Color_process
    inRange(imgHSV, Scalar(iLowH,iLowS,iLowV), Scalar(iHighH,iHighS,iHighV), imgThresholded);

    //open--close
    element = getStructuringElement(MORPH_RECT, Size(3,3));
    morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
    morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
    GaussianBlur(imgThresholded,imgThresholded,Size(7,7),0,0);

    //findcontours
    vector<vector<Point>> contours, contours1, contours2, contours3, contours4, contours5, contours6, contours7, contours8;
    int g_cannyLowThreshold = 20;
    
    Canny(imgThresholded, imgCanny, g_cannyLowThreshold, (g_cannyLowThreshold * 3));
    
    findContours(imgCanny, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours1, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours2, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours3, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours4, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours5, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours6, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours7, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(imgCanny, contours8, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    //find max_contours
    double length_max = 0;
    int i;
    int k = 0;
    if(contours.size() > 0)
    {
        for(i = 0; i < contours.size(); i++)
        {
            if(arcLength(contours[i], 0) > length_max)
            {
                length_max = arcLength(contours[i], 0);
                k = i;
            }
        }
    }
        drawContours(frame, contours, k, Scalar(120, 0, 0), 4);
        drawContours(frame, contours1, k-2, Scalar(120, 0, 0), 2);
        drawContours(frame, contours2, k-3, Scalar(120, 0, 0), 2);
        drawContours(frame, contours3, k-4, Scalar(120, 0, 0), 2);
        drawContours(frame, contours4, k-5, Scalar(120, 0, 0), 2);
        drawContours(frame, contours5, k-6, Scalar(120, 0, 0), 2);
        drawContours(frame, contours6, k-7, Scalar(120, 0, 0), 2);
        drawContours(frame, contours7, k-8, Scalar(120, 0, 0), 2);
        drawContours(frame, contours8, k-1, Scalar(120, 0, 0), 2);

        imshow("Color", imgThresholded);
        imshow("video", frame);
}