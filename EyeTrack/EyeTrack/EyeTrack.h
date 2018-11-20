#pragma once
#ifndef  _EYETRACK_H
#define  _EYETRACK_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/stitching.hpp"
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cv;

//typedef struct _rect
//{
//	int x;
//	int y;
//}RECT;

#define ROI
#define TYPENUM		10
#define START_X		335
#define START_Y		84
#define END_X		930
#define END_Y		689

vector<Mat> m_ImgMap;
vector<Mat> m_TypeMap[TYPENUM];

#endif
