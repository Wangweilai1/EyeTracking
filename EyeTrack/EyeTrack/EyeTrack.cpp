// EyeTrack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/stitching.hpp"
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cv;

typedef struct _rect
{
	int x;
	int y;
}RECT;

#define TYPENUM 10
vector<Mat> m_ImgMap;
vector<Mat> m_TypeMap[TYPENUM];
int main()
{
#if 1
	VideoCapture cap;
	cap.open("D:/GitHub/EyeTrack/data/lvxiaobo02.wmv"); //打开视频,以上两句等价于VideoCapture cap("E://2.avi");

	if (!cap.isOpened())//如果视频不能正常打开则返回
		return -1;

	int imgIndex = 1;
	while (1)
	{
		uchar *ptrMap = nullptr, *ptrIO = nullptr;
		Mat frame, imgGray;
		cap >> frame;//等价于cap.read(frame);
		if (frame.empty())//如果某帧为空则退出循环
			break;
		cvtColor(frame, imgGray, COLOR_BGR2GRAY);
		resize(imgGray, imgGray, Size(600, 400));
		if (imgIndex == 1)
		{
			m_ImgMap.push_back(imgGray);
			m_TypeMap[0].push_back(imgGray);
		}
		else
		{
#pragma omp parallel for
			for (int typeNum = 0; typeNum < TYPENUM; ++typeNum)
			{
				int minUnMatchNum = 24000000;

				for (int index = 0; index < m_TypeMap[typeNum].size(); ++index)
				{
					int unMatchNum = 0;
					//vector<RECT> m_postion;
					for (int cy = 0; cy < m_TypeMap[typeNum][index].rows; ++cy)
					{
						ptrMap = m_TypeMap[typeNum][index].ptr<uchar>(cy);
						ptrIO = imgGray.ptr<uchar>(cy);
						for (int cx = 0; cx < m_TypeMap[typeNum][index].cols; ++cx)
						{
							if (ptrMap[cx] != ptrIO[cx])
							{
								//RECT rcRegion;
								//rcRegion.x = cx;
								//rcRegion.y = cy;
								//m_postion.push_back(rcRegion);
								unMatchNum += 1;
							}
						}
					}
					minUnMatchNum = min(minUnMatchNum, unMatchNum);
				}
				if (minUnMatchNum > 100000 && minUnMatchNum != 24000000)
				{
					vconcat(m_ImgMap[typeNum], imgGray, m_ImgMap[typeNum]);
					m_TypeMap[0].push_back(imgGray);
					break;
				}
			}
		}
		//string imIdex = format("D:/GitHub/EyeTrack/data/%d.jpg", imgIndex);
		//imwrite(imIdex.c_str(), imgGray);
		//imshow("video", imgGray);
		imgIndex += 1;
		//waitKey(20);//每帧延时20毫秒
	}
	imwrite("D:/GitHub/EyeTrack/data/0000.jpg", m_ImgMap);
	cap.release();//释放资源
#endif
#if 0
	std::vector< cv::Mat > vImg;
	cv::Mat rImg;

	string img = format("D:/GitHub/EyeTrack/data/%d.jpg", 1);
	//vImg.push_back(cv::imread("D:/GitHub/EyeTrack/data//0.jpg"));
	vImg.push_back(cv::imread("D:/GitHub/EyeTrack/data//1.jpg"));
	vImg.push_back(cv::imread("D:/GitHub/EyeTrack/data//2.jpg"));
	vImg.push_back(cv::imread("D:/GitHub/EyeTrack/data//3.jpg"));
	vImg.push_back(cv::imread("D:/GitHub/EyeTrack/data//4.jpg"));
	vImg.push_back(cv::imread("D:/GitHub/EyeTrack/data//5.jpg"));

	cv::Stitcher stitcher = cv::Stitcher::createDefault();

	unsigned long AAtime = 0, BBtime = 0; //check processing time
	AAtime = cv::getTickCount(); //check processing time

	cv::Stitcher::Status status = stitcher.stitch(vImg, rImg);

	BBtime = cv::getTickCount(); //check processing time 
	printf("Time consuming: %.2lf sec \n", (BBtime - AAtime) / cv::getTickFrequency()); //check processing time

	if (cv::Stitcher::OK == status)
		cv::imshow("Stitching Result", rImg);
	else
		printf("Stitching fail.");

	cv::waitKey(0);
#endif
	return 0;
}

