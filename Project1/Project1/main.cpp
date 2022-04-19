#include "Headers.h"
#include "Tree.h"
#include "Algo.h"

int reg_num = 0;
int bitnum = 0;
double thresU = 0;
double thresVar = 0;
int cur_block = -1;

/** Main Function
  * @author CuiYuxin
  * @input 1.�����ַ
  * @input 2.ԭ��ͼ
  * @input 3.ת���Ҷ�ͼ�ļ���
  * @input 4.ת��RNAMC�ļ���
  * @input 5.ͬ��췧ֵ
  * @input 6.��ֵ��ֵ
  * @input 7.���ֵ
  * @input 8.�з� 1 ˮƽ 0��ֱ
  */
int main(int argc, char** argv)
{
	int nmb = 0;
	Mat img;
	string imagePath = samples::findFile(argv[1]);
	img = imread(imagePath, 0); //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
	if (argc == 8 && !img.empty())
	{
		time_t start, end, time, convergeStart, convergeEnd, convergeTime; //��ʱ����
		Mat imggest = Mat::zeros(img.size(), img.type());
		int num = atoi(argv[7]);
		int M = img.rows; //ͼ��߶�
		int N = img.cols; //ͼ����
		double epsilon = atof(argv[4]);
		vector<doubleCoordinate> C; //���������
		vector<colorListStandard> P; //������ɫ��
		vector<char> Q; //������������
		Tree tree;
		treeIterator it(tree);
		thresU = atof(argv[5]);
		thresVar = atof(argv[6]);
		Mat sketch(img.size(), CV_8UC1);  //��������ͼ��
		start = clock(); //Start building tree
		treeIterator(tree);
		Algo::BuildTree(img, it, P, C, num, epsilon, doubleCoordinate(0, 0, M - 1, N - 1));

		

		
	}



	
}