#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int i, j, v = 0, g = 0, b = 0, r = 0, m, n, c = 0, o, k = 0, p1 = 0, p2 = 0;

Mat colorextract(Mat img, int v, int r, int g, int b)

{

	int x, y, z;
    Mat img1(img.rows, img.cols, CV_8UC3, Scalar(255, 255, 255));
    for (i = 0; i < img.rows; i++)
	{
    for (j = 0; j < img.cols; j++)
		{
			x = img.at<Vec3b>(i, j)[2];
			y = img.at<Vec3b>(i, j)[1];
			z = img.at<Vec3b>(i, j)[0];

			if (x >= (r - v) && x <= (r + v) && y >= (g - v) && y <= (g + v) && z >= (b - v) && z <= (b + v))
			{
				img1.at<Vec3b>(i, j)[2] = x;
				img1.at<Vec3b>(i, j)[1] = y;
				img1.at<Vec3b>(i, j)[0] = z;
			}
		}
	}
	int a = img1.rows / 2;
	for (j = 8; j < img1.cols; j++)
	if (img1.at<Vec3b>(a, j)[2] >= 255 - 25 && img1.at<Vec3b>(a, j)[2] <= 255 && img1.at<Vec3b>(a, j)[1] >= 255 - 25 && img1.at<Vec3b>(a, j)[1] <= 255 && img1.at<Vec3b>(a, j)[0] >= 255 - 25 && img1.at<Vec3b>(a, j)[0] <= 255)

	{
		n = j;
		break;
	}
	return img1;
}

void display_detected(Mat img, Mat det)
{
   Mat img1(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
	Mat gray(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));

	cvtColor(img, gray, CV_BGR2GRAY);

	GaussianBlur(gray, gray, Size(3, 3), 2, 2);

	vector<Vec3f> circles;

	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows, 100, 30, 1, 30);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(img1, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(img1, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		if (cvRound(circles[i][0]) < 52)
		{
			c++; p1 = 0; k = 0;
		}
		if (c>0 && cvRound(circles[i][0]) >= 550 && cvRound(circles[i][0]) <= 580 && p1 == 0 && k == 0)
			p1 = 1;
	}
	if (p1 == 1)
	{
		p2++;
		printf("score of player 1=%d\n", p2);
		printf("score of player 2=0\n");
		k = 1;
		p1 = 0;
	}
	cout << endl;
	namedWindow("Detected Circle: ", WINDOW_NORMAL);
}

int main()
{
	Mat frame;
	VideoCapture vc("new.mp4");     //Link to the video- https://drive.google.com/open?id=0ByXHIzRXNFdaanhKQm1vbDVFM0U
	namedWindow("Win", WINDOW_NORMAL);

	while (1)
	{
		vc >> frame;

		if (frame.data != NULL)
		{
			imshow("Win", frame);
			display_detected(frame, colorextract(frame, v, r, g, b));
		}
		if (frame.data == NULL)
		{
			printf("final score of player 1=%d\n", p2 + 1);
			printf("final score of player 2=0\n");
			break;
		}
		if (waitKey(50) == ' ')
			break;
	}
}
