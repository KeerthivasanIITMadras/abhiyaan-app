#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

void getContours(cv::Mat imgDilate, cv::Mat img)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i>hierarchy;
	cv::findContours(imgDilate, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);//finding contours
	for (int i = 0; i < contours.size(); i++)
	{	
		float area= cv::contourArea(contours[i]);
		float peri = arcLength(contours[i], true);
		if (peri > 200 && peri < 300)	//sorting the contours according to perimeter
		{	
			if (area > 500 && area < 3790)//sorting the contours according to area
			{	
				cv::drawContours(img, contours, i, cv::Scalar(255, 0, 0), 2);//drawing the contours
			}
		}
	}
}
int main()
{
	std::string path = "Resources/bolt_test_pothole.mp4";
	cv::VideoCapture cap(path);
	cv::Mat img;

	int canmin = 0;
	int canmax = 255;

	int threshmin = 210;//I used trackbars to find these values
	int threshmax = 255;

	int a1 = 1;
	while (true)
	{
		cap.read(img);//reading image of that frame
		cv::Mat imgGray;
		cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);//coverting the image to grey
		cv::Mat imgBlur;
		GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 5, 0);//Blurring the grey image
		cv::Mat imgthreshold;
		cv::threshold(imgGray, imgthreshold,threshmin,threshmax, 1);//converting the grey image to a 
																	//threshold image to filter out unwanted objects
																	//Here i am using type 1 threshold function
		cv::Mat imgCanny;
		Canny(imgthreshold, imgCanny,canmin, canmax);//Converting to canny image
		cv::Mat imgErode;
		cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(a1, a1));
		cv::erode(imgCanny, imgErode, kernel);//making the edges plotted by canny function lighter 
		getContours(imgErode, img);//function to plot the contours
		cv::imshow("Video", img);//Playing the video image by image
		cv::waitKey(6);
	}
		
}