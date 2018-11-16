// EyeTrack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/stitching.hpp"
#include <iostream>

using namespace std;
using namespace cv;

typedef struct _rect
{
	int x;
	int y;
}RECT;

vector<Mat> m_ImgMap;
vector<RECT> m_postion;
int main()
{
#if 1
	VideoCapture cap;
	cap.open("D:/GitHub/EyeTrack/data/lvxiaobo02.wmv"); //����Ƶ,��������ȼ���VideoCapture cap("E://2.avi");

	if (!cap.isOpened())//�����Ƶ�����������򷵻�
		return -1;

	Mat frame;
	int imgIndex = 0;
	while (1)
	{
		cap >> frame;//�ȼ���cap.read(frame);
		if (frame.empty())//���ĳ֡Ϊ�����˳�ѭ��
			break;

		static int imgIndex = 0;
		if (imgIndex == 0)
		{
			m_ImgMap.push_back(frame);
		}
		else
		{
			for (int typeNum = 0; typeNum < m_ImgMap.size(); ++typeNum)
			{
				for (int cy = 0; cy < m_ImgMap[typeNum].rows; cy += 2)
				{
					for (int cx = 0; cx < m_ImgMap[typeNum].cols; cx += 2)
					{
						if (m_ImgMap[typeNum].data[3 * cy + cx] != frame.data[3 * cy + cx])
						{
							RECT rcRegion;
							rcRegion.x = cx;
							rcRegion.y = cy;
							m_postion.push_back(rcRegion);
						}
					}
				}
			}
		}
		string imIdex = format("D:/GitHub/EyeTrack/data/%d.jpg", imgIndex);
		imwrite(imIdex.c_str(), frame);
		//imshow("video", frame);
		imgIndex += 1;
		//waitKey(20);//ÿ֡��ʱ20����
	}
	cap.release();//�ͷ���Դ
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

