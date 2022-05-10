#pragma once
#include "Headers.h"
#include "Tree.h"
/** Implement the algotirhm
  * @author CuiYuxin */
class Algo
{
public:
	//STC
	static bool JudgeSameBlock(double epsilon, Mat img, doubleCoordinate dots);
	static void BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<doubleCoordinate>& C, int& num, double epsilon, doubleCoordinate dots); //�ָ�ԭͼ.��������R.��ɫ��P
	static void MakeImggest(Mat imggest, vector<colorListStandard>& P, vector<doubleCoordinate> C); //����gestͼ��
	//DP
	static void EnCode(Mat R, Size s, vector<char>& Q);
	static void Decode(Mat R, Size s, const vector<char>& Q);
	static bool IsSameBlock(const Mat img, doubleCoordinate dots, int margin);
};

