#pragma once
#include "Headers.h"
#include "Tree.h"
/** Implement the algotirhm
  * @author CuiYuxin */
class Algo
{
public:
	static bool JudgeSameBlock(double epsilon, Mat img, doubleCoordinate dots);
	static void BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<doubleCoordinate>& C, int& num, double epsilon, doubleCoordinate dots);//�ָ�ԭͼ.��������R.��ɫ��P
};

