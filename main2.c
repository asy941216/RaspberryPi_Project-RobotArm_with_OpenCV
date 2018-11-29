#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "/usr/include/mysql/mysql.h"
#include <raspicam/raspicam_cv.h>
#include <opencv2/core/mat.hpp>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/imgproc.hpp>  
#include <opencv2/highgui.hpp>

#define DBHOST "192.168.137.3"
#define DBUSER "pi"
#define DBPASS "raspberry"
#define DBNAME "test"

MYSQL *connector;
MYSQL_RES *result;
MYSQL_ROW row;

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	int data;
	int color;
	char color_code;
	connector = mysql_init(NULL);
	if (!mysql_real_connect(connector, DBHOST, DBUSER, DBPASS, DBNAME, 3306, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(connector));
		return 0;
	}

	printf("MYSQL(rpidb) opened.\n");

	raspicam::RaspiCam_Cv cap;

	cap.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CAP_PROP_FRAME_HEIGHT, 960);

	if (!cap.open())
	{
		cerr << "Error opening the camera" << endl;
		return -1;
	}

	if (argc == 1)
	{
		fputs("There is no input option.", stderr);
		return 1;
	}
	else
		color = (int)argv[1][0];

	int LowH = 0;
	int HighH = 0;

	int LowS = 0;
	int HighS = 0;

	int LowV = 0;
	int HighV = 0;

	if (color == 'r')
	{
		LowH = 160;
		HighH = 190;

		LowS = 110;
		HighS = 230;

		LowV = 0;
		HighV = 255;
	}
	else if (color == 'g')
	{
		LowH = 40;
		HighH = 80;

		LowS = 100;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color == 'b')
	{
		LowH = 90;
		HighH = 110;

		LowS = 100;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color == 'y')
	{
		LowH = 20;
		HighH = 40;

		LowS = 110;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	color_code = color;
	
	int fps = cap.get(CAP_PROP_FPS);
	cout << fps << endl;

	Mat img_input, img_hsv, img_binary;
	cap.grab();
	cap.retrieve(img_input);

	cvtColor(img_input, img_hsv, COLOR_BGR2HSV);

	inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);

	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(img_binary, img_labels, stats, centroids, 8, CV_32S);


	int max = -1, idx = 0;
	int array[numOfLables];
	for (int j = 1; j < numOfLables; j++)
	{
		array[j] = stats.at<int>(j, CC_STAT_AREA);
		if (max < array[j])
		{
			max = array[j];
			idx = j;
		}
	}

	int left = stats.at<int>(idx, CC_STAT_LEFT);
	int top = stats.at<int>(idx, CC_STAT_TOP);
	int width = stats.at<int>(idx, CC_STAT_WIDTH);
	int height = stats.at<int>(idx, CC_STAT_HEIGHT);
	int right = left + width;
	int bottom = top + height;

	rectangle(img_input, Point(left, top), Point(right, bottom),
		Scalar(0, 0, 255), 4);

	imwrite("processed_image.jpg", img_input);
	printf("jpg file is created.\n");

	char query[1024];

	sprintf(query, "delete from sample");

	sprintf(query, "insert into sample (x,y,color) values (%d,%d,'%c')", (left + right) / 2, (top + bottom) / 2, color_code);
	
	mysql_close(connector);

	return 0;
}