#pragma once
#include "opencv.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

struct colorListStandard //��׼������ɫ��
{
	uchar g1, g2, g3, g4;
};

struct doubleCoordinate //���ϽǼ����½�����
{
	pair<int, int> dot1;
	pair<int, int> dot2;
};

