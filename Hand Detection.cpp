#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

int x=0, y=0,a,b;
int main()
{
	VideoCapture cap(0); 

	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); 

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); 
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); 
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); 
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;
		
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 
	
		Mat imgThresholded;
	
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); 

		
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Image", imgThresholded); 
		imshow("Original", imgOriginal); 
		int c = 0;
		x = 0;
		y = 0;
			for (int i = 0; i < imgThresholded.rows; i++)
		{
			for (int j = 0; j < imgThresholded.cols; j++)
			{
				if (imgThresholded.at<uchar>(i, j)> 255 - 50 && imgThresholded.at<uchar>(i, j)<= 255)
				{
					x=x+i;
					y=y+j;
					c++;
				}
			}
	
		}
			x = x / c;
			y = y / c;
		if ((y - b) < 0)
			printf("left\n");
		else if ((y - b) > 0)
			printf("right\n");
		else
			printf("same\n");
		a = x; 
		b = y;
		
		waitKey(5);
	}
	return 0;
}
